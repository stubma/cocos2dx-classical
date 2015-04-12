import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;


public abstract class BaseExporter {
	protected Workbook getWorkbook(File f) {
		Workbook book = null;
		try {
	        String fileName = f.getName();
	        if (f.getName().endsWith(".xls")) {
	        	book = new HSSFWorkbook(new FileInputStream(f));
	        }
	        if (fileName.endsWith(".xlsx")) {
	        	book = new XSSFWorkbook(new FileInputStream(f));
	        }
        } catch (Exception e) {
        }
		
		return book;
	}
	
	protected String firstCapital(String s) {
		s = s.trim();
		return s.substring(0, 1).toUpperCase() + s.substring(1);
	}
	
	protected String firstLowercase(String s) {
		s = s.trim();
		return s.substring(0, 1).toLowerCase() + s.substring(1);
	}
	
	protected void writeFile(String filePath, String sets) throws IOException {
		BufferedOutputStream buff = null;
		FileOutputStream outStream = null;
		try {
			outStream = new FileOutputStream(new File(filePath));
			buff = new BufferedOutputStream(outStream);
			buff.write(sets.getBytes("utf-8"));
			buff.flush();
			buff.close();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				outStream.close();
				buff.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	public void export(File file) throws IOException {
		Workbook book = getWorkbook(file);
		for(int s = 0; s < 1; s++) {
			Sheet sheet = book.getSheetAt(s);
			doExport(book, sheet, file);
		}
	}
	
	public abstract void doExport(Workbook book, Sheet sheet, File file) throws IOException;
}
