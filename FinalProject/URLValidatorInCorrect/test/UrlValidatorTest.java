import org.junit.rules.ErrorCollector;
import org.junit.Rule;
import org.junit.Test;
import junit.framework.TestCase;

import static org.hamcrest.core.IsEqual.equalTo;
//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


public class UrlValidatorTest extends TestCase {
	private boolean failStatus = true;

	public UrlValidatorTest(String testName) {
	   super(testName);
	}
	
    @Rule
    public ErrorCollector collector = new ErrorCollector();

    @Test
    public void testManualTest()
    {
        //You can use this function to implement your manual testing
        UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        try {
            collector.checkThat(validator.isValid(null), equalTo(false));
        } catch (Error e) {
            collector.addError(e);
        }
        try {
            collector.checkThat(validator.isValid("http"), equalTo(false));
        } catch (Error e) {
            collector.addError(e);
        }
        try {
            collector.checkThat(validator.isValid("abc.def.google.com"), equalTo(false));
        } catch (Error e) {
            collector.addError(e);
        }
        try {
            collector.checkThat(validator.isValid("http://www....google.com"), equalTo(false));
        } catch (Error e) {
            collector.addError(e);
        }
        try {
            collector.checkThat(validator.isValid("http://www.@@$.com"), equalTo(false));
        } catch (Error e) {
            collector.addError(e);
        }
        try {
            collector.checkThat(validator.isValid("http://localhost:8000"), equalTo(false));
        } catch (Error e) {
            collector.addError(e);
        }
        try {
            collector.checkThat(validator.isValid("https://www.pir.com"), equalTo(true));
        } catch (Error e) {
            collector.addError(e);
        }
        try {
            collector.checkThat(validator.isValid("http://www.google.com"), equalTo(true));
        } catch (Error e) {
            collector.addError(e);
        }
        try {
            collector.checkThat(validator.isValid("https://www.google.org"), equalTo(true));
        } catch (Error e) {
            collector.addError(e);
        }
        collector.checkThat(validator.isValid("http://www.google.com/search"), equalTo(true));
        try {
            collector.checkThat(validator.isValid("https://www.google.com/search?source=hp&ei=VzGXWrTyKKGJ0wKdt6-gBA&q=hello&oq=hello"), equalTo(true));
        } catch (Error e) {
            collector.addError(e);
        }

    }
    public boolean testPart(UrlValidator validator, String testUrl)
    {
 	   return validator.isValid(testUrl);
    }

    public void failMessage(String testUrl)
    {
 	   System.out.println("FAILED: " + testUrl);
    }
    
    //scheme//
    public void testYourFirstPartition(){
 	   String append = "";
 	   String prepend = "www.google.com";
 	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

 	   String[] good = {"http://","ftp://","h3t://","file://", ""};
 	   String[] bad = {"http:///","http:/"};

 	   System.out.println("TESTING GOOD SCHEMES");

 	   for (int i = 0; i < good.length; i++) {
 		   //valid schemes should pass
 		   if (!testPart(validator, append + good[i] + prepend))
 		   {
 			  failMessage(append + good[i] + prepend);
 		   }
 	   }

 	   System.out.println("TESTING BAD SCHEMES");

 	   for (int i = 0; i < bad.length; i++) {
 		   //invalid schemes pass as invalid
 		   if (!testPart(validator, append + bad[i] + prepend))//if test fails do nothing
 		   {
 		   }
 		   else 
 		   {
 			   if (failStatus)
 			   {
 				   failMessage(append + bad[i] + prepend);
 			   }
 		   }
 	   }
    }
    
    
    //authority//
    public void testYourSecondPartition(){
 	   String append = "http://";
 	   String prepend = "";
 	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

 	   String[] good = {"amazon.com","google.com","google.ca","0.0.0.0","255.255.255.255"};

 	   String[] bad = {"256.256.256.256","1.2.3.4.5","-1.-1.-1.-1",".com",".ca",""};

 	   System.out.println("TESTING GOOD AUTHORITIES");

 	   for (int i = 0; i < good.length; i++) {
 		   //valid authorities pass as valid
 		   if (testPart(urlVal, append + good[i] + prepend))
 		   {	 
 		   }
 		   else
 		   {
 			   if (failStatus)
 			   {
 				   failMessage(append + good[i] + prepend);
 			   }
 		   }
 	   }

 	   System.out.println("TESTING BAD AUTHORITY");

 	   for (int i = 0; i < bad.length; i++) {
 		   //test++;

 		   //invalid authorities pass as invalid
 		   if (!testPart(urlVal, append + bad[i] + prepend))
 		   {
 			  //NOTHING.. these should, expected to fail
 		   }
 		   else
 		   {
 			   if (failStatus)
 			   {
 				   failMessage(append + bad[i] + prepend);
 			   }
 		   }
 	   }
    }
    
    //ports//
    public void testYourThirdPartition(){
 	   String append = "http://www.google.com";
 	   String prepend = "";
 	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

 	   String[] good = {":8000",":88",":200",":111"};
 	   String[] bad = {":av6", ":65555", ":12b"};

 	   System.out.println("TESTING GOOD PORTS");

 	  for (int i = 0; i < good.length; i++) {
		   //valid authorities pass as valid
		   if (testPart(validator, append + good[i] + prepend))
		   {	 
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + good[i] + prepend);
			   }
		   }
	   }

 	   System.out.println("TESTING BAD PORTS");

 	   for (int i = 0; i < bad.length; i++) {
 		   //invalid ports should fail
 		   if (!testPart(validator, append + bad[i] + prepend))//if test fails do nothing
 		   {failMessage(append + bad[i] + prepend);
 		   }
 		   else 
 		   {
 		   }
 	   }
    }
    
    //ports//
    public void testYourFourthPartition(){
 	   String append = "http://www.google.com";
 	   String prepend = "";
 	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

 	   String[] good = {"/good","/good2","/123","/extr"};
 	   String[] bad = {"///", "/..//garbage", "/././/"};

 	   System.out.println("TESTING GOOD PATHS");

 	   for (int i = 0; i < good.length; i++) {
 		   //valid ports should pass
 		   if (!testPart(validator, append + good[i] + prepend))
 		   {
 			  failMessage(append + good[i] + prepend);
 		   }
 	   }

 	   System.out.println("TESTING BAD PATHS");

 	   for (int i = 0; i < bad.length; i++) {
 		   //invalid ports should fail
 		   if (!testPart(validator, append + bad[i] + prepend))//if test fails print fail message
 		   { failMessage(append + bad[i] + prepend);
 		   }
 		   else 
 		   {
 		   }
 	   }
    }
    
    
    public void testYourFifthPartition(){
  	   String append = "http://www.google.com";
  	   String prepend = "";
  	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

  	   String[] good = {"?action=view","?action=edit&mode=up","?action=edit;mode=up",""};
  	   String[] bad = {":a6h", ":1122232", ":b6j5b"};

  	   System.out.println("TESTING GOOD QUERY");

  	  for (int i = 0; i < good.length; i++) {
 		   //valid authorities pass as valid
 		   if (testPart(validator, append + good[i] + prepend))
 		   {	 
 		   }
 		   else
 		   {
 			   if (failStatus)
 			   {
 				   failMessage(append + good[i] + prepend);
 			   }
 		   }
 	   }

  	   System.out.println("TESTING BAD QUERY");

  	   for (int i = 0; i < bad.length; i++) {
  		   //invalid ports should fail
  		   if (!testPart(validator, append + bad[i] + prepend))//if test fails do nothing
  		   {failMessage(append + bad[i] + prepend);
  		   }
  		   else 
  		   {
  		   }
  	   }
     }
    
    
    //You need to create more test cases for your Partitions if you need to
    @Test
    public void testIsValid()
    {
        //You can use this function for programming based testing

    }

}
