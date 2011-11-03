package browsefs;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.firefox.FirefoxDriver;


public class BrowserModule implements Runnable
{

	public BrowserModule() {
		System.out.println("The classpath is: " + System.getProperty("java.class.path", "."));

	}

	public void run() {
        	WebDriver driver = new FirefoxDriver();
		driver.get("http://www.facebook.com");
		System.out.println("Success");
	}
	
	

}
