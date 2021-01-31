
public class StringExample {

	public static void main(String[] args) {
		String str1 = "welcome!";
		String str2 = "welcome!";
		
		String str3 = new String ("Hello");
		String str4 = "Hello";
		
		char[] c = {'a', 'b', 'c'};
		String str5 = new String(c);
		
		String str6 = new String (str4);
		
		System.out.println(str1 == str2);
		System.out.println(str1.equals(str2));
		
		System.out.println(str3 == str4);
		System.out.println(str3.equals(str4));
		
		System.out.println(str5 + str6);
		System.out.println(str5.concat(str6));
		
		int length = str1.length();
		System.out.println(length);
		
		for (int i = 0; i < length; i++)
			System.out.println(str1.charAt(i));
		
		System.out.println(str4.toLowerCase());
		System.out.println(str4.toUpperCase());
		
		System.out.println(str4.indexOf('l'));
		
		String sub1 = str2.substring(2);
		String sub2 = str2.substring(1,3);
		System.out.println(sub1);
		System.out.println(sub2);
		
		double d = 4.56;
		boolean f = false;
		String s1 = String.valueOf(d);
		String s2 = String.valueOf(f);
		
		System.out.println(s1 + " " + s2);

	}

}

