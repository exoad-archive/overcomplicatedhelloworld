// and indexedOHWCCHain ...
//S: 1 type
//S: 2 function definitions
case object BlankHWCChain extends HWCChain[Char] {
  override def ce = ' '
  override def next = WHWCChain
}
