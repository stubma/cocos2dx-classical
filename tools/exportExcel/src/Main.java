import gnu.getopt.Getopt;
import gnu.getopt.LongOpt;
import org.apache.poi.util.SystemOutLogger;

import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FilenameFilter;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Main {
	private interface ExportListener {
		void onSingleFileStartExporting(File file, int index);
		void onSingleFileExported(Exception e);
		void onAllCompleted();
	}

	public static void main(String[] args) throws Exception {
		// build options
		LongOpt[] opts = new LongOpt[4];
		opts[0] = new LongOpt("console", LongOpt.NO_ARGUMENT, null, 'c');
		opts[1] = new LongOpt("language", LongOpt.REQUIRED_ARGUMENT, null, 'l');
		opts[2] = new LongOpt("jsonDir", LongOpt.OPTIONAL_ARGUMENT, null, 'j');
		opts[3] = new LongOpt("excelDir", LongOpt.REQUIRED_ARGUMENT, null, 'e');
		Getopt getopt = new Getopt("exportExcel", args, "l:j:e:c", opts);
		getopt.setOpterr(false);

		// parse arguments
		boolean consoleMode = false;
		String jsonDir = "";
		String excelDir = "";
		String language = "";
		int ch;
		while((ch = getopt.getopt()) != -1) {
			switch(ch) {
				case 'c':
					consoleMode = true;
					break;
				case 'l':
					language = getopt.getOptarg();
					break;
				case 'j':
					jsonDir = getopt.getOptarg();
					break;
				case 'e':
					excelDir = getopt.getOptarg();
					break;
			}
		}

		// check running mode
		if(consoleMode) {
			runInConsoleMode(language, excelDir, jsonDir);
		} else {
			runInUiMode();
		}
	}

	private static void runInConsoleMode(String language, String excelDir, String jsonDir) {
		File dir = new File(excelDir);
		File[] files = dir.listFiles(new FilenameFilter() {
			@Override
			public boolean accept(File dir, String name) {
				String ext = name.substring(name.lastIndexOf('.') + 1);
				if(name.startsWith("~") || name.startsWith(".")) {
					return false;
				} else if(ext != null && (ext.equalsIgnoreCase("xls") || ext.equalsIgnoreCase("xlsx"))) {
					return true;
				} else {
					return false;
				}
			}
		});
		final int len = files.length;
		export(language, files, jsonDir, new ExportListener() {
			@Override
			public void onSingleFileStartExporting(File file, int index) {
				System.out.print(String.format("Exporting(%d/%d) %s", index + 1, len, file.getAbsolutePath()));
			}

			@Override
			public void onSingleFileExported(Exception e) {
				if(e != null) {
					System.out.println("...Error: " + e.getLocalizedMessage());
				} else {
					System.out.println("...Done");
				}
			}

			@Override
			public void onAllCompleted() {
			}
		});
	}

	private static void runInUiMode() {
		// window frame
		JFrame f = new JFrame("Excel Exporter");
		Container container = f.getContentPane();
		container.setLayout(new GridLayout(3, 1));

		// help area
		StringBuilder buf = new StringBuilder("1. first row can be human readable column name\n");
		buf.append("2. second row is reversed and not used now\n");
		buf.append("3. third row should be English name of column, first letter will be automatically converted to upppercase\n");
		buf.append("4. fourth row is case-insensitive column type name, can be bool, byte, int, string, float, stringarray, intarray, boolarray, floatarray and luafunc\n");
		buf.append("5. first column must be a primary key column\n");
		buf.append("6. if you don't want a column to be generated, just leave column name or type blank");
		JTextArea t = new JTextArea(buf.toString());
		t.setEditable(false);
		t.setBackground(f.getBackground());
		t.setBorder(BorderFactory.createTitledBorder("Help"));
		container.add(t);

		// center layout
		Container bottom = new Container();
		bottom.setLayout(new GridLayout(1, 2));
		container.add(bottom);

		// bottom, error label
		final JTextArea errorArea = new JTextArea("Ready");
		errorArea.setEditable(false);
		errorArea.setBackground(f.getBackground());
		errorArea.setBorder(BorderFactory.createTitledBorder("Message"));
		container.add(errorArea);

		// add combo
		String[] s = {
				"Excel to Json/Lua",
				"Excel to Json/C++"
		};
		final JComboBox cmb = new JComboBox(s);
		cmb.setBorder(BorderFactory.createTitledBorder("Export Type"));
		bottom.add(cmb);

		// json path editbox
		final JTextField pathField = new JTextField();
		pathField.setBorder(BorderFactory.createTitledBorder("Json File Folder"));
		bottom.add(pathField);

		// add button
		JButton btn = new JButton("Select Excel Files");
		btn.setBackground(Color.GREEN);
		bottom.add(btn);

		// show window
		f.pack();
		f.setVisible(true);

		// set window location
		Dimension winSize = Toolkit.getDefaultToolkit().getScreenSize();
		f.setLocation((winSize.width - f.getWidth()) / 2, (winSize.height - f.getHeight()) / 2);

		// handle button
		btn.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent evt) {
				JFileChooser fileChooser = new JFileChooser(System.getProperty("user.home"));
				FileNameExtensionFilter filter = new FileNameExtensionFilter("Excel Files", "xls", "xlsx");
				fileChooser.setMultiSelectionEnabled(true);
				fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
				fileChooser.setFileFilter(filter);
				int returnVal = fileChooser.showOpenDialog(fileChooser);
				if (returnVal == JFileChooser.APPROVE_OPTION) {
					final File files[] = fileChooser.getSelectedFiles();
					Thread t = new Thread(new Runnable() {
						@Override
						public void run() {
							// reset message
							errorArea.setForeground(Color.BLACK);

							// call export
							final int len = files.length;
							String language = cmb.getSelectedIndex() == 0 ? "lua" : "c++";
							export(language, files, pathField.getText(), new ExportListener() {
								@Override
								public void onSingleFileStartExporting(File file, int index) {
									errorArea.setText("Exporting:" + file.getAbsolutePath() + "---" + (index + 1) + "/" + len);
								}

								@Override
								public void onSingleFileExported(Exception e) {
									if(e != null) {
										errorArea.setForeground(Color.RED);
										errorArea.append("\n" + e.getLocalizedMessage());
									}
								}

								@Override
								public void onAllCompleted() {
									// if no error, show Done
									if(errorArea.getForeground() == Color.BLACK) {
										errorArea.setText("Done");
									}
								}
							});
						}
					});
					t.start();
				}
			}
		});
	}

	private static void export(String language, File[] files, String jsonDir, ExportListener listener) {
		// create exporter
		JsonExporter je = new JsonExporter();
		BaseExporter we = null;
		if(language.equalsIgnoreCase("lua")) {
			we = new LuaExporter();
			je.setGenerateIndexColumn(true);
			je.setIndexStartFromZero(false);
		} else {
			we = new CppExporter();
		}

		// set option
		we.addOption("jsonDir", jsonDir);

		// export every file
		try {
			int len = files.length;
			for (int i = 0; i < len; i++) {
				listener.onSingleFileStartExporting(files[i], i);

				// export json
				je.export(files[i]);

				// export wrapper
				we.export(files[i]);
				listener.onSingleFileExported(null);
			}
		} catch(Exception e) {
			listener.onSingleFileExported(e);
		} finally {
			listener.onAllCompleted();
		}
	}
}
