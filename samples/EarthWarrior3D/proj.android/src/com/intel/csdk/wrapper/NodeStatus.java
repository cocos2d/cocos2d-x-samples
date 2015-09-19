package com.intel.csdk.wrapper;

public class NodeStatus {

	private String mNodeName;
	private int mNodeStatus;
	
	public NodeStatus(String node, int status) {
		mNodeName = node;
		mNodeStatus = status;
	}
	
	public String getNodeName(){
		return mNodeName;
	}
	
	public int getNodeStatus(){
		return mNodeStatus;
	}
	
	public boolean compare(NodeStatus temp){
		
		if(this.getNodeName().equalsIgnoreCase(temp.getNodeName())){
			return true;
		}
		return false;
	}
}
