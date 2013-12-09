import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


public class Main
{

    public static void main(String[] args)
    {
        String[] inputFiles = {"sample.comfort"};
        String[] outputFiles = new String[inputFiles.length];
        String[] expectedOutputFiles = new String[inputFiles.length];
        int filesChecked = 0;
        int errorCount = 0;
        
        // automate creation of output and expected output filename strings
        for (int i = 0; i < inputFiles.length; i++)
        {
            outputFiles[i] = inputFiles[i].concat(".output");
            expectedOutputFiles[i] = inputFiles[i].concat(".expected");
        }
        
        // run lexer on each of the input test files
        //  and create output files
        for (int i = 0; i < inputFiles.length; i++)
        {
            // look up how to do this part later  
            // some kind of bash command to run ./lexer << inputFiles[i] >> outputFiles[i]
            //  where inputFiles[i] is an input comfort file and outputFiles[i]
            //  is the output file name
        }
        
        // compare output files with expected output files
        for (int i = 0; i < inputFiles.length; i++)
        {
            try
            {
                BufferedReader realOutput = 
                        new BufferedReader(new FileReader("testFiles/".concat(inputFiles[i])));
                BufferedReader expectedOutput = 
                        new BufferedReader(new FileReader("testFiles/".concat(inputFiles[i])));
            
                filesChecked++;
                
                String real;
                String expected;
                
                while ((real = realOutput.readLine()) != null)
                {
                    expected = expectedOutput.readLine();
                
                    
                    if (!real.equals(expected))
                    {
                           System.out.println("ERROR: on tests for file = " + inputFiles[i]
                                   + ", expected = " + expected + ", real = " + real);
                           errorCount++;
                    }
                }

                realOutput.close(); 
                expectedOutput.close();
            } 
            catch (IOException e)
            {
                System.out.println("Error on test " + inputFiles[i]);
            }
        }
        
        System.out.println("Testing complete. Files checked = " + filesChecked + ", errors = " + errorCount);
    }

}
