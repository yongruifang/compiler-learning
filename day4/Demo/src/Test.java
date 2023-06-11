import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class Test {
    public static void main(String[] args) throws Exception {
            // create a CharStream that reads from standard input
            CharStream input = CharStreams.fromFileName("src/Arraytest.txt"); // create a lexer that feeds off of input CharStream
            ArrayInitLexer lexer = new ArrayInitLexer(input); // create a buffer of tokens pulled from the lexer
            CommonTokenStream tokens = new CommonTokenStream(lexer); // create a parser that feeds off the tokens buffer
            ArrayInitParser parser = new ArrayInitParser(tokens);
            ParseTree tree = parser.array(); // begin parsing at init rule
            System.out.println(tree.toStringTree(parser)); // print LISP-style tree }
    }
}