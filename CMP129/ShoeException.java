public class ShoeException extends Exception
{
	private String m;
	
	public ShoeException(String m)
	{
		this.m = m;
	}
	
	public String toString()
	{
		return m;
	}
}