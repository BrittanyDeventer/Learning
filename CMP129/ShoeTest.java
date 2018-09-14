/*
* Brittany Deventer
* CMP 129
* Assignment 9
*
*/

public class ShoeTest
{
	public static void main(String[] args)
	{
		try 
		{
			//test shoe constructor and toString
			Shoe w = new Shoe("Y128A", 7, 1);
			Shoe b = new Shoe("Y128A", 7, 1);
			System.out.println(w);
			
			//test shoeType constructor and toString
			ShoeType x = new ShoeType(w, 12);
			System.out.println(x);
			
			ShoeType y = new ShoeType("MQ43T", 6, 2, 3);
			ShoeType z = new ShoeType("MQ43T", 6.5, 1, 44);
			System.out.println(y + "\n" + z);
			ShoeType c = new ShoeType("MQ43T", 6.5, 1, 44);		
			
			//test shoeInventory constructor and toString
			int size = 3;
			ShoeInventory n = new ShoeInventory(size);
			System.out.println(n);
			
			//test empty delete
			//n.delete(3);
			
			//test add()
			System.out.println("Testing Add() \n");
			n.add(y);
			System.out.println(n);
			
			//test duplicate add
			//n.add(y);
			
			n.add(x);
			n.add(z); 
			System.out.println(n);
			
			//test full add
			//n.add(x);
			
			//test find
			System.out.println("testing find() \n " + n.find(w));
			
			//test delete()
			System.out.println("Testing Delete \n" + n.delete(2) + "\n new inventory: " + n);
			
			//test equals
			System.out.println("Shoe equals test \n   " + w.equals(b));
			
			System.out.println("shoe type equals test \n  " + c.equals(z));
			
			ShoeInventory m = new ShoeInventory(size);		
			m.add(y);
			m.add(x);
			System.out.println("M: " + m); 
			System.out.println("Shoe Inventory equals test: " + n.equals(m));
			
			//test clones
			Shoe t = (Shoe) w.clone();
			ShoeType r = (ShoeType) z.clone();
			ShoeInventory s = (ShoeInventory) n.clone();
			
			System.out.println(t.equals(w));
			System.out.println(z.equals(r));
			System.out.println(n.equals(s));
		}
		catch(ShoeException e)
		{
			System.out.println("Error: " + e);
		}
		catch(Exception e)
		{
			System.out.println("Catch All Error: " + e);
		}
	}
}