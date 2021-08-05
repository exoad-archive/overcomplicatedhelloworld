/**
  This is a 'H'-element, followed by the 'e'-Element. 
S: 1 type 
S: 2 functions
*/
case object HHWCChain extends HWCChain[Char] with ContentProvider[Char] {
  override def ce = 'H'
  override def next = eHWCChain
}
