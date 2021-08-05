//S: 1 type 
//S: 2 function definitions
case object rHWCChain extends HWCChain[Char] {
  override def ce = 'r'
  override def next = new indexedLHWCChain (3) 
}
