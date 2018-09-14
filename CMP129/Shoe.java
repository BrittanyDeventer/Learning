/*
* Brittany Deventer
* CMP 129
* Assignment 9
*
*/

public class Shoe implements Cloneable
{
	private String id;
	private double size;
	private int color;
	private static int counter;
	
	/*Constructor*/
	public Shoe(String i, double s, int c) throws ShoeException
	{
		setId(i);
		setSize(s);
		setColor(c);
		counter ++;
	}
	
	/*Setter Getters*/
	public void setId(String i) throws ShoeException
	{
		if(i == null || i.equals(""))
			throw new ShoeException("Invalid ID.");
		else
			id = i;
	}
	public String getId()
	{
		return id;
	}
	
	public void setSize(double s) throws ShoeException
	{
		if(s < 1.0)
			throw new ShoeException("Invalid Size.");
		else
			size = s;
	}
	public double getSize()
	{
		return size;
	}
	
	public void setColor(int c) throws ShoeException
	{
		if(c < 1)
			throw new ShoeException("Invalid Color.");
		else
			color = c;
	}
	public int getColor()
	{
		return color;
	}
	
	/*Overrides*/
	public String toString()
	{
		return "id: " + id + ", size: " + size + ", color: " + color;
	}
	
	protected void finalize()
	{
		System.out.println("The shoe with id " + id + " and size of " + size + ", and color of " + color + " will now be deleted.");
		counter --;
	}
	
	protected Object clone() throws CloneNotSupportedException
	{
		return (Shoe) super.clone();
	}
	
	public boolean equals(Shoe s)
	{
		if(s == null)
			return false;
		if(s.getClass() != Shoe.class)
			return false;
		
		Shoe temp;
		temp = (Shoe) s;
		
		if(id == temp.id && size == temp.size && color == temp.color)
			return true;
		else 
			return false;
	}
	
	/*Behaviors*/	
	public int getCount()
	{
		return counter;
	}
}