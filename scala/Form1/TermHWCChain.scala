/*
   Here is the only case, where hasNext returns false. 
   For scientists: If you're interested in terminating programs, this type is 
   for you!

S: 1 type 
S: 3 function definitions
*/ 
case object TermHWCChain extends HWCChain[Char] {
  override def ce = '\n'
  override def hasNext (): Boolean = false 
  override def next = TermHWCChain // dummy - has next is always false
}
