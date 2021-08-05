// and indexedOHWCCHain ...
//S: 1 type 
//S: 1 function definition
//S: 1 function call 
//S: 1 control structure 
case class indexedOHWCChain (i: Int) extends theOThing {
  override def next = i match { 
    case 1 => BlankHWCChain
    case _ => rHWCChain
  }
}
