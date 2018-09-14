/*
* Brittany Deventer
* CMP 129
* Assignment 9
*
*/

public class ShoeInventory implements Cloneable
{
	private ShoeType[] typeArray;
	private static int counter; //# of cells used
	private int arraySize; //size of array 
	
	/*Constructors*/
	public ShoeInventory(int size)
	{
		if(size == 0)
			System.out.println("Cannot set array to size 0."); 
		else
		{
			counter = 0;
			arraySize = size;
			typeArray = new ShoeType[arraySize];
		}
	}
	
	/*Behaviors*/
	public boolean isFull()
	{
		if(counter == arraySize)
			return true;
		else
			return false;
	}
	
	public boolean isEmpty()
	{
		if(counter == 0)
			return true;
		else
			return false;
	}
	
	public int getCapacity()
	{
		return arraySize;
	}
	
	public int getNumItems()
	{
		return counter; 
	}
	
	public int find(Shoe s)
	{
		if(isEmpty()) //if array is empty
			return -3;
		else if(s == null) //if parameter is null
			return -2;
		else
		{
			for(int i = 0; i < counter; i++)
			{
				if(typeArray[i].getShoe().equals(s)) 
					return i;
			}
			
			return -1; //if no match found
		}
	}
	
	public void add(ShoeType t) throws ShoeException
	{
		if(isFull())
			throw new ShoeException("Cannot Add: Array is full.");
		else if(find(t.getShoe()) >= 0)
			throw new ShoeException("Cannot Add: Duplicate.");
		else
		{
			typeArray[counter] = t;
			counter ++;
		}
	}
	
	public ShoeType delete(int i) throws ShoeException
	{
		ShoeType temp;
		
		if(isEmpty())
			throw new ShoeException("Cannot Delete: Array is empty");
		else if(i < 0 || i > counter -1)
			throw new ShoeException("Cannot Delete: No shoeType at that index");
		else
		{
			//store ShoeType to be deleted in temp
			temp = typeArray[i];
			
			if(i == arraySize - 1) //if i is last index
			{
				typeArray[i] = null;
			}
			else if(i == 0) //if i is first index
			{
				for(int k = 0; k < counter - 1; k++)
				{
					typeArray[k] = typeArray[k + 1];
				}
				//last index to null
				typeArray[counter - 1] = null;
			}
			else
			{
				for(int k = i; k < counter - 1; k++)
				{
					typeArray[k] = typeArray[k + 1];
				}
				//last index to null
				typeArray[counter - 1] = null;				
			}
			counter --;
		}
		
		return temp;
	}
	
	/*Overrides*/
	public boolean equals(Object s)
	{
		int n = 0;
		if(s == null)
			return false;
		if(s.getClass() != ShoeInventory.class)
			return false;
		
		ShoeInventory temp;
		temp = (ShoeInventory) s;
		
		//if both are empty
		if(isEmpty() && temp.isEmpty())
			return true;
		else
		{
			for(int i = 0; i < counter; i++)
			{
				if(typeArray[i].equals(temp.typeArray[i])) 
				{
					n++;
					
					if(n == counter && arraySize == temp.getCapacity())
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	
	public String toString()
	{
		String m = "\n";
		if(isEmpty())
			return "Inventory is empty";
		else
		{
			for(int i = 0; i < counter; i++)
			{
				int n = i + 1;
				m += "Item " + n + ": " + typeArray[i] + "\n";
			}
		}
		return m;
	}
	
	protected Object clone() throws CloneNotSupportedException
	{
		return (ShoeInventory) super.clone();
	}
}