package ep1;

import ep1.ArrayInitParser.ArrayContext;
import ep1.ArrayInitParser.ValueContext;
/**
 * Short To Unicode Listener
 */
public class ArrayInitS2UListener extends ArrayInitBaseListener{
    @Override
    public void enterArray(ArrayContext ctx) {
        System.out.print("\"");
    }
    @Override
    public void enterValue(ValueContext ctx) {
        // Assumes no nested array initializers
        int value = Integer.valueOf(ctx.INT().getText());
        System.out.printf("\\u%04x", value);
    }
    @Override
    public void exitArray(ArrayContext ctx) {
        System.out.print("\"");
    }
    @Override  
    public void exitValue(ValueContext ctx) {  
        super.exitValue(ctx);
    }
}
