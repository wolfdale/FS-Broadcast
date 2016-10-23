# FS-Broadcast
<p>File BroadCast System over UDP Protocol</p>
<p>A distributed system where each node broadcast it's file system (not whole
file system, just content of directory, it can be configured to broadcast whole
file system) to other broadcasting nodes. it's a form of communication where 
different files are scattered over the network of stystem/nodes, here a node 
broadcast what files it have to other nodes, and in response it get the list
of files other nodes have. it's a dynamic system in which each node requires
to broadcast file list to others. if the file is deleted from any node whole
system will know that file has been deleted from that particular node.</p>

<p>Here each node knows the full topology of network like how many nodes are 
there in network, what type of files particular node have. Usually in centralized
network a node requesting a file has to query the central node for loaction of
file, later on it establishes a direct communication with node for file transfer.
<p>

