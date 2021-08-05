/*  
    As we all know, the future is functional programming. 

    And one of the mantras of pure functional programming is, to avoid mutable data 
    as hell. Using case classes and case objects allows us to create very small,
    immutable Flight-Weight-Pattern like objects (Singletons, if you like).

    I'm choosing scala, because its compiled to bytecode for the JVM and therefore very 
    portable. I could of course have implemented it in Java, but as we all know,
    Javacode is boilerplaty, while scala is a concise language.     

    S: for easy grepping of scoring hints. 
    Scoring summary: 

        1 import 
        3 control structures
        8 function calls
       22 function definitions
       14 type definitions
       14 files: Seperate files speed up the compilation process, 
          if you only happen to make a local change. 
*/

/**
   To change the content and replace it with something else later, we generate 
   a generic Content trait, which will be 'Char' in the beginning, but could be Int or
   something. 

S:   1 type definition. 
S:   1 function 
*/
trait ContentProvider [T] {
  // ce is the content-element, but we like to stay short and lean. 
  def ce () : T 
}
