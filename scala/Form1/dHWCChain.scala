//S: 1 type
//S: 2 function definitions
case object dHWCChain extends HWCChain[Char] {
  override def ce = 'd'
  override def next = TermHWCChain
}
