//S: 1 type
//S: 2 function definitions
case object WHWCChain extends HWCChain[Char] {
  override def ce = 'W'
  override def next = new indexedOHWCChain (2) 
}
