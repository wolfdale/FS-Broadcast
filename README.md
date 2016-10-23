# FS-Broadcast
<h3>File BroadCast System over UDP Protocol</h3>
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
Incase central node is down the file transfer can not be possible.<p>

<p>This system uses a distributed approach, where each node knows the file loaction
in network, thus making it easy to transfer files directly without any dependence
on any central node.<p>

<h3>Concept of Hidden Node</h3>
<p>it's a concept which I designed, to make a node hidden from network, yet it
knows the full topology of network. it never broadcast its content to other node
but listens to the broadcast of other node.(Still figuring out the use case)<p>

<h3>Concept of Privileges</h3>
<p>With this system, a node only broadcast files local to itself. it never 
broadcast the file list which it have received from other nodes. The reason
for this is <u>Privileges</u> sometime a node may have confidential files, which
other node need not to know about. For this a configuration file is kept, so a 
node knows what other node in network it needs to broadcast.</p>



