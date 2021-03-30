# Bug log

BVH树中每个节点应当包含多个Object。如果多个Object的包围盒重叠，就将这些Object放在同一个节点上，不然会导致遮盖。