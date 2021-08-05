//S:  1 import, for the tailcall annotation later. 
import annotation._

/**
   HWCChain is a Chain of HelloWordCharacters, but as a lean, concise language, 
   we do some abbrev. here. 
   We need hasNext () and next (), which is the iterator Pattern.

S: 1 type 
S: 2 functions definitions 
S: 4 function calls
S: 1 if 
*/
trait HWCChain[T] extends Iterator [HWCChain[T]] with ContentProvider[T] {
  // tailrec is just an instruction for the compiler, to warn us, if this code 
  // can't be tail call optimized. 
  @tailrec 
  final def go () : Unit = {
    // ce is our ContentProvider.ce 
    System.out.print (ce);
    // and here is our iterator at work, hasNext and next:  
    if (hasNext ()) next ().go ()
  }
  // per default, we have a next element (except our TermHWWChain, see close to bottom) 
  // this follows the DRY-principle, and reduces the code drastically.
  override def hasNext (): Boolean = true 
}
