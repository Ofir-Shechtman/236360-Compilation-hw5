#ifndef EX5_CODE_GEN
#define EX5_CODE_GEN

#include <vector>
#include <string>
using namespace std;
//this enum is used to distinguish between the two possible missing labels of a conditional branch in LLVM during backpatching.
//for an unconditional branch (which contains only a single label) use FIRST.
enum BranchLabelIndex {FIRST, SECOND};
typedef pair<int,BranchLabelIndex> pii;

class CodeBuffer{
	CodeBuffer();
	CodeBuffer(CodeBuffer const&);
    void operator=(CodeBuffer const&);
	std::vector<std::string> globalDefs;
public:
    std::vector<std::string> buffer;
    static CodeBuffer &instance();

	// ******** Methods to handle the code section ******** //

	//generates a jump location label for the next command, writes it to the buffer and returns it
	std::string genLabel();

	//writes command to the buffer, returns its location in the buffer
	int emit(const std::string &command);

    int nextInst() const;

	//gets a pair<int,BranchLabelIndex> item of the form {buffer_location, branch_label_index} and creates a list for it
	static vector<pair<int,BranchLabelIndex>> makelist(pair<int,BranchLabelIndex> item);

	//merges two lists of {buffer_location, branch_label_index} items
	static vector<pair<int,BranchLabelIndex>> merge(const vector<pair<int,BranchLabelIndex>> &l1,const vector<pair<int,BranchLabelIndex>> &l2);

	/* accepts a list of {buffer_location, branch_label_index} items and a label.
	For each {buffer_location, branch_label_index} item in address_list, backpatches the branch command 
	at buffer_location, at index branch_label_index (FIRST or SECOND), with the label.
	note - the function expects to find a '@' char in place of the missing label.
	note - for unconditional branches (which contain only a single label) use FIRST as the branch_label_index.
	example #1:
	int loc1 = emit("br label @");  - unconditional branch missing a label. ~ Note the '@' ~
	bpatch(makelist({loc1,FIRST}),"my_label"); - location loc1 in the buffer will now contain the command "br label %my_label"
	note that index FIRST referes to the one and only label in the line.
	example #2:
	int loc2 = emit("br i1 %cond, label @, label @"); - conditional branch missing two labels.
	bpatch(makelist({loc2,SECOND}),"my_false_label"); - location loc2 in the buffer will now contain the command "br i1 %cond, label @, label %my_false_label"
	bpatch(makelist({loc2,FIRST}),"my_true_label"); - location loc2 in the buffer will now contain the command "br i1 %cond, label @my_true_label, label %my_false_label"
	*/
	void bpatch(const vector<pair<int,BranchLabelIndex>>& address_list, const std::string &label);
	
	//prints the content of the code buffer to stdout
	void printCodeBuffer();

	// ******** Methods to handle the data section ******** //
	//write a line to the global section
	void emitGlobal(const string& dataLine);
	//print the content of the global buffer to stdout
	void printGlobalBuffer();

};

class BooleanE{
public:
    vector<pair<int,BranchLabelIndex>> trueList;
    vector<pair<int,BranchLabelIndex>> falseList;
    BooleanE()=default;
    void add(int label, BranchLabelIndex idx, bool which_list){
        pair<int, BranchLabelIndex> item(label, idx);
        if(which_list)
            trueList = CodeBuffer::makelist(item);
        else
            falseList = CodeBuffer::makelist(item);
    }
    void add(int true_label, BranchLabelIndex true_idx,
             int false_label, BranchLabelIndex false_idx){
        pair<int, BranchLabelIndex> item1(true_label, true_idx);
        trueList = CodeBuffer::makelist(item1);
        pair<int, BranchLabelIndex> item2(false_label, false_idx);
        falseList = CodeBuffer::makelist(item2);
    }
};


#endif

