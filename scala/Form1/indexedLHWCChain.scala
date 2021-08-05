/**
  depending on the l-number, we either have another l as next, or an o, or the d. 
S: 1 type 
S: 1 function definition
S: 2 function calls
S: 1 control structure (match/case) 
*/
case class indexedLHWCChain (i: Int) extends theLThing {
  override def next = i match { 
    case 1 => new indexedLHWCChain (2) 
    case 2 => new indexedOHWCChain (1) 
    case _ => dHWCChain
  }
}
