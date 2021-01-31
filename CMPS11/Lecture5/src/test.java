
public class test {

	public static void main(String[] args) {
	     String str = "abs";
	     for(int i = 0; i < str.length(); i++){
	          str = str.substring(0, i) + (char)((int)str.charAt(i)+1) + str.substring(i+1);
	          
	          // "" + 'b' + "bs" == "bbs"
	          // "b" + 'c' + "s" = "bcs"
	          // "bc" + 't' + "" = "bct"
	          System.out.println(str);
	     }
	}
}
