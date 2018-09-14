/*
* Brittany Deventer
* CMP 129
* Assignment 9
*
*/

public class ShoeType implements Cloneable
{
	private Shoe shoe;
	private int quantity;
	
	/*Setter Getters*/
	public void setQuantity(int q) throws ShoeException
	{
		if(q < 1)
			throw new ShoeException("Unable to set quantity.");
		else
			quantity = q;
	}
	public int getQuantity()
	{
		return quantity;
	}
	
	public Shoe getShoe()
	{
		return shoe;
	}
	
	/*Constructors*/
	public ShoeType(Shoe s, int q) throws ShoeException
	{
		shoe = s; 
		setQuantity(q);
	}
	
	public ShoeType(String i, double s, int c, int q) throws ShoeException
	{
		shoe = new Shoe(i, s, c);
		setQuantity(q);
	}
	
	/*Overrides*/
	public String toString()
	{
		String n = shoe + ", quantity: " + quantity; 
		return n;
	}
	
	public boolean equals(Object s)
	{
		if(s == null)
			return false;
		if(s.getClass() != ShoeType.class)
			return false;
		
		ShoeType temp;
		temp = (ShoeType) s;
		
		if(shoe.equals(temp.getShoe()) && temp.quantity == quantity)
			return true;
		else
			return false;
	}
	
	protected Object clone() throws CloneNotSupportedException
	{
		return (ShoeType) super.clone();
	}
}