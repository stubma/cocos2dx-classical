
public class CellFormatException extends Exception {
    private static final long serialVersionUID = 1L;
    
    private int mRow;
    private int mCol;
    
    public CellFormatException(int row, int col) {
    	super(String.format("Cell at %d:%d has error", row, col));
    	mRow = row;
    	mCol = col;
    }
    
	public int getRow() {
	    return mRow;
    }

	public int getCol() {
	    return mCol;
    }
}
