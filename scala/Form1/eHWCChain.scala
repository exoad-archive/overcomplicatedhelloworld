/*
  and here is the 'e'-Element, followed by l-Element 1, which is a new Type

S: 1 type 
S: 2 functions
*/
case object eHWCChain extends HWCChain[Char] {
  override def ce = 'e'
  override def next = new indexedLHWCChain (1) 
}
