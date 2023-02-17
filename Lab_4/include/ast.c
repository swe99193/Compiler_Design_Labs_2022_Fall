#ifndef __AST_C__
#define __AST_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* Note: can only be used by list node, struct layout should be same as AST_List*/
/* append to the end of linkedlist */
void addChild(AST_Node* parent, AST_Node* child){
	AST_List *p = (AST_List *)parent;
	AST_Node *tmp = p->children;

	if (!tmp){	// first child
		p->children = child;
	}
	else{
		while(tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = child;
	}
}

/* Note: can only be used by node that has *next, struct layout should be same AST_Node*/
/* append to the end of linkedlist */
void addNext(AST_Node* parent, AST_Node* child){
	AST_Node *tmp = parent->next;

	if (!tmp){	// first sibling
		parent->next = child;
	}
	else{
		while(tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = child;
	}
}

/* ------------------AST NODE MANAGEMENT-------------------- */
/* The basic node */
// AST_Node *new_ast_node(Node_Type type, AST_Node *left, AST_Node *right){
// 	// allocate memory
// 	AST_Node *v = malloc (sizeof (AST_Node));
	
// 	// set entries
// 	v->type = type;
// 	v->left = left;
// 	v->right = right;
	
// 	// return the result
// 	return v;
// }

/* Declarations */
AST_Node *DeclarationList_node(){
	AST_DeclarationList *v = malloc (sizeof (AST_DeclarationList));
	
	v->type = DECL_LIST;
	v->children = NULL;
	// printf("DeclarationList created\n");
	// fprintf(stderr, "DeclarationList created\n");

	return (AST_Node *) v;
}

AST_Node *Declaration_node(AST_Node* idList, AST_Node* Type_node){
	AST_Declaration *v = malloc (sizeof (AST_Declaration));
	
	v->type = DECL;
	v->idList = idList;
	v->Type_node = Type_node;
	v->next = NULL;
	
	return (AST_Node *) v;
}

/* identifier, const, type */
AST_Node *IdentifierList_node(){
	AST_IdentifierList *v = malloc (sizeof (AST_IdentifierList));
	
	v->type = ID_LIST;
	v->children = NULL;

	return (AST_Node *) v;
}

AST_Node *id_node(char* name, bool redeclared){
	AST_Id *v = malloc (sizeof (AST_Id));
	
	v->type = ID_NODE;
	strcpy(v->name, name);
	// v->dtype is set after declaration
	v->redeclared = redeclared;
	v->next = NULL;
	v->entry = NULL;
	
	return (AST_Node *) v;
}

AST_Node *var_node(char* name){
	AST_var *v = malloc (sizeof (AST_var));
	
	v->type = VAR_NODE;
	strcpy(v->name, name);
	v->arrayidx = NULL;
	v->entry = NULL;
	// v->ref_type set after symtab search
	// FIXME: link to symtab entry
	
	return (AST_Node *) v;
}

AST_Node *ArraySize_node(int low, int high, int dimension){
	AST_ArraySize *v = malloc (sizeof (AST_ArraySize));
	
	v->type = ARRAYSIZE;
	v->low = low;
	v->high = high;
	v->dimension = dimension;
	v->next = NULL;
	
	return (AST_Node *) v;
}

AST_Node *Arrayidx_node(AST_Node *expr, int dimension){
	AST_Arrayidx *v = malloc (sizeof (AST_Arrayidx));
	
	v->type = ARRIDX;
	v->expr = expr;
	v->dimension = dimension;
	v->next = NULL;
	
	return (AST_Node *) v;
}


AST_Node *const_node(dtype dtype, Value val){
	AST_Const *v = malloc (sizeof (AST_Const));
	
	v->type = CONST_NODE;
	v->dtype = dtype;
	v->val = val;
	
	return (AST_Node *) v;
}


AST_Node *Type_node(int dtype, int arraydtype){
	AST_Type *v = malloc (sizeof (AST_Type));
	
	v->type = TYPE_NODE;
	v->dtype = dtype;
	v->arraydtype = arraydtype;
	v->children = NULL;
	
	return (AST_Node *) v;
}


/* function declaration */

AST_Node *SubprogramDeclarationList_node(){
	AST_SubprogramDeclarationList *v = malloc (sizeof (AST_SubprogramDeclarationList));
	
	v->type = SubProgDecl_LIST;
	v->children = NULL;
	
	return (AST_Node *) v;
}

AST_Node *SubprogramDeclaration_node(AST_Node * head, AST_Node * declList, AST_Node *compstmt){
	AST_SubprogramDeclaration *v = malloc (sizeof (AST_SubprogramDeclaration));
	
	v->type = SubProgDecl;
	v->head = head;
	v->declList = declList;
	v->compstmt = compstmt;
	v->next = NULL;

	return (AST_Node *) v;
}

AST_Node *SubprogramHead_node(enum dtype dtype, AST_Node * id, AST_Node * arguments, enum dtype return_type){
	AST_SubprogramHead *v = malloc (sizeof (AST_SubprogramHead));
	
	v->type = SubProgHead;
	v->dtype = dtype;
	v->id = id;
	v->arguments = arguments;
	v->return_type = return_type;
	return (AST_Node *) v;
}

AST_Node *Arguments_node(AST_Node * paramList){
	AST_Arguments *v = malloc (sizeof (AST_Arguments));
	
	v->type = ARGUMENTS;
	v->paramList = paramList;
	
	return (AST_Node *) v;
}

AST_Node *ParameterList_node(){
	AST_ParameterList *v = malloc (sizeof (AST_ParameterList));
	
	v->type = PARAM_LIST;
	v->children = NULL;
	
	return (AST_Node *) v;
}

AST_Node *Params_node(AST_Node * idList, AST_Node * Type_node){
	AST_Params *v = malloc (sizeof (AST_Params));
	
	v->type = PARAMS;
	v->idList = idList;
	v->Type_node = Type_node;
	v->next = NULL;

	return (AST_Node *) v;
}


/* Statements */

AST_Node *CompoundStatement_node(AST_Node * stmtList){
	AST_CompoundStatment_node *v = malloc (sizeof (AST_CompoundStatment_node));
	
	v->type = COMPSTMT;
	v->stmtList = stmtList;
	v->next = NULL;
	
	return (AST_Node *) v;
}

AST_Node *StatementList_node(){
	AST_StatementList *v = malloc (sizeof (AST_StatementList));
	
	v->type = STMT_LIST;
	v->children = NULL;
	
	return (AST_Node *) v;
}

AST_Node *Assignment_node(AST_Node * variable, AST_Node * expr){
	AST_Assignment *v = malloc (sizeof (AST_Assignment));
	
	v->type = ASSIGN_NODE;
	v->variable = variable;
	v->expr = expr;
	v->next = NULL;
	
	return (AST_Node *) v;
}


AST_Node *ProcedureStatement_node(AST_Node * id, AST_Node * exprList){
	AST_ProcedureStatement *v = malloc (sizeof (AST_ProcedureStatement));
	
	v->type = FUNC_CALL;
	v->id = id;
	v->exprList = exprList;
	v->next = NULL;
	
	return (AST_Node *) v;
}


AST_Node *ifelse_node(AST_Node * expr, AST_Node * ifstmt, AST_Node * elsestmt){
	AST_ifelse *v = malloc (sizeof (AST_ifelse));
	
	v->type = IFELSE_NODE;
	v->expr = expr;
	v->ifstmt = ifstmt;
	v->elsestmt = elsestmt;
	v->next = NULL;
	
	return (AST_Node *) v;
}

AST_Node *while_node(AST_Node * expr, AST_Node * stmt){
	AST_while *v = malloc (sizeof (AST_while));
	
	v->type = WHILE_NODE;
	v->expr = expr;
	v->stmt = stmt;
	v->next = NULL;
	
	return (AST_Node *) v;
}

/* Expression */

AST_Node *ExpressionList_node(){
	AST_ExpressionList *v = malloc (sizeof (AST_ExpressionList));
	
	v->type = EXPR_LIST;
	v->children = NULL;
	
	return (AST_Node *) v;
}

AST_Node *Expression_node(AST_Node* subExpr, int dtype){
	AST_Expression *v = malloc (sizeof (AST_Expression));
	
	v->type = EXPR;
	v->subExpr = subExpr;
	v->dtype = dtype;
	v->next = NULL;

	return (AST_Node *) v;
}

AST_Node *arithm_node(int op, AST_Node* Lexpr, AST_Node* Rexpr){
	AST_arithm *v = malloc (sizeof (AST_arithm));
	
	v->type = ARITHM_NODE;
	v->op = op;
	v->Lexpr = Lexpr;
	v->Rexpr = Rexpr;

	v->next = NULL;

	// FIXME: assume left and right expresion return same type
	// if any type is Uninit_type, set Uninit_type
	int Ltype = ((AST_Expression *)Lexpr)->dtype;
	int Rtype = ((AST_Expression *)Rexpr)->dtype;
	v->dtype = (Ltype==Uninit_type || Rtype==Uninit_type) ? Uninit_type : ((AST_Expression*)Lexpr)->dtype;

	return (AST_Node *) v;
}

AST_Node *relation_node(int op, AST_Node* Lexpr, AST_Node* Rexpr){
	AST_relation *v = malloc (sizeof (AST_relation));
	
	v->type = REL_NODE;
	v->op = op;
	v->Lexpr = Lexpr;
	v->Rexpr = Rexpr;

	v->next = NULL;

	// FIXME: assume left and right expresion return same type
	int Ltype = ((AST_Expression *)Lexpr)->dtype;
	int Rtype = ((AST_Expression *)Rexpr)->dtype;
	v->dtype = (Ltype==Uninit_type || Rtype==Uninit_type) ? Uninit_type : ((AST_Expression*)Lexpr)->dtype;
	return (AST_Node *) v;
}

AST_Node *bool_node(int op, AST_Node* Lexpr, AST_Node* Rexpr){
	AST_bool *v = malloc (sizeof (AST_bool));
	
	v->type = BOOL_NODE;
	v->op = op;
	v->Lexpr = Lexpr;
	v->Rexpr = Rexpr;

	v->next = NULL;

	// FIXME: assume left and right expresion return same type
	if(Lexpr && Rexpr){
		// AND, OR
		int Ltype = ((AST_Expression *)Lexpr)->dtype;
		int Rtype = ((AST_Expression *)Rexpr)->dtype;
		v->dtype = (Ltype==Uninit_type || Rtype==Uninit_type) ? Uninit_type : ((AST_Expression*)Lexpr)->dtype;
	}else if(Lexpr){
		// NOT
		v->dtype = ((AST_Expression *)Lexpr)->dtype;
		printf("[ast] create NOT ast\n");// DEBUG
	}else{
		fprintf(stderr, "[ERRROR] ast: bool node receive NULL Lexpr & Rexpr\n");
	}

	return (AST_Node *) v;
}


/* Tree Traversal */

void ast_print_node(AST_Node *node){
	if(node == NULL)
		return;

	/* temp nodes */
	AST_DeclarationList *DeclList_ptr;
	AST_Declaration *Decl_ptr;
	AST_IdentifierList *IdList_ptr;
	AST_Id *Id_ptr;
	AST_var *Var_ptr;
	AST_ArraySize *Arrsize_ptr;
	AST_Arrayidx *Arridx_ptr;
	AST_Const *Const_ptr;
	AST_Type *Type_ptr;
	AST_SubprogramDeclarationList *SubProgDeclList_ptr;
	AST_SubprogramDeclaration *SubProgDecl_ptr;
	AST_SubprogramHead *SubProgHead_ptr;
	AST_Arguments *Arguments_ptr;
	AST_ParameterList *ParamList_ptr;
	AST_Params *Params_ptr;
	AST_CompoundStatment_node *CompStmt_ptr;
	AST_StatementList *StmtList_ptr;
	AST_Assignment *Assignment_ptr;
	AST_ProcedureStatement *ProcedureStmt_ptr;
	AST_ifelse *Ifelse_ptr;
	AST_while *While_ptr;
	AST_ExpressionList *ExprList_ptr;
	AST_Expression *Expr_ptr;
	AST_arithm *Arithm_ptr;
	AST_relation *Relation_ptr;
	AST_bool *Bool_ptr;

	int data_type;
	int node_type = node->type;
	
	switch(node_type){
		case BASIC_NODE:
			printf("Basic Node\n");
			break;
		case DECL_LIST:
			printf("Declaration List\n");
			break;
		case DECL:
			printf("Declaration \n");
			break;
		case ID_LIST:
			printf("Id List \n");
			break;
		case ID_NODE:
			Id_ptr = (AST_Id *) node;
			printf("Id: %s \n", Id_ptr->name);
			break;
		case VAR_NODE:
			Var_ptr = (AST_var *) node;
			// FIXME: if it is array, print array index
			printf("variable: %s \n", Var_ptr->name);
			break;
		case ARRAYSIZE:
			Arrsize_ptr = (AST_ArraySize *) node;
			printf("array size, dim:%d, (low, high): (%d, %d)\n", Arrsize_ptr->dimension, Arrsize_ptr->low, Arrsize_ptr->high);
			break;
		case ARRIDX:
			Arridx_ptr = (AST_Arrayidx *) node;
			printf("array index, dim:%d\n", Arridx_ptr->dimension);
			break;
		case CONST_NODE:
			Const_ptr = (struct AST_Const *) node;
			data_type = Const_ptr->dtype;
			switch(data_type){
				case Int_type:
					printf("Constant, int, value = %d\n", Const_ptr->val.ival);
					break;
				case Real_type:
					printf("Constant, real, value = %.2f\n", Const_ptr->val.fval);
					break;
			}
			break;
		case TYPE_NODE:
			Type_ptr = (AST_Type *) node;
			data_type = Type_ptr->dtype;
			switch(data_type){
				case Int_type:
					printf("Type, int\n");
					break;
				case Real_type:
					printf("Type, real\n");
					break;
				case Array_type:
					printf("Type, array\n");
					break;
			}
			break;
		case SubProgDecl_LIST:
			printf("Subprogram decl List\n");
			break;
		case SubProgDecl:
			printf("Subprogram decl \n");
			break;
		case SubProgHead:
			SubProgHead_ptr = (AST_SubprogramHead *) node;
			if (SubProgHead_ptr->dtype == Function_type)
				printf("Subprogram decl head, Function, return type: %d\n", SubProgHead_ptr->return_type);
			else if(SubProgHead_ptr->dtype == Procedure_type)
				printf("Subprogram decl head, Procedure, return type: %d\n", SubProgHead_ptr->return_type);
			else
				printf("Subprogram decl head, ????? functype\n");
			break;
		case ARGUMENTS:
			printf("Arguments \n");
			break;
		case PARAM_LIST:
			printf("Params list \n");
			break;
		case PARAMS:
			printf("params \n");
			break;
		case COMPSTMT:
			printf("Compound Stmt \n");
			break;
		case STMT_LIST:
			printf("Stmt List \n");
			break;
		case ASSIGN_NODE:
			printf("assign stmt \n");
			break;
		case FUNC_CALL:
			printf("Function call stmt \n");
			break;
		case IFELSE_NODE:
			printf("Ifelse stmt \n");
			break;
		case WHILE_NODE:
			printf("While stmt \n");
			break;
		case EXPR_LIST:
			printf("Expression List\n");
			break;
		case EXPR:
			printf("Dummy Expression \n");
			break;
		case ARITHM_NODE:
			Arithm_ptr = (AST_arithm *) node;
			int Arithm_op = Arithm_ptr->op;
			if(Arithm_op == Add_op)
				printf("Arithmetic Expression: + (add) \n");
			else if(Arithm_op == Sub_op)
				printf("Arithmetic Expression: - (subtract) \n");
			else if(Arithm_op == Mul_op)
				printf("Arithmetic Expression: * (multiply)\n");
			else if(Arithm_op == Div_op)
				printf("Arithmetic Expression: / (divide) \n");
			break;
		case REL_NODE:
			Relation_ptr = (AST_relation *) node;
			int Rel_op = Relation_ptr->op;
			if(Rel_op == Greater_op)
				printf("Relation Expression: > \n");
			else if(Rel_op == Less_op)
				printf("Relation Expression: < \n");
			else if(Rel_op == Greater_equal_op)
				printf("Relation Expression: >= \n");
			else if(Rel_op == Less_equal_op)
				printf("Relation Expression: <= \n");
			else if(Rel_op == Equal_op)
				printf("Relation Expression: == \n");
			else if(Rel_op == Not_equal_op)
				printf("Relation Expression: != \n");
			break;
		case BOOL_NODE:
			Bool_ptr = (AST_bool *) node;
			int Bool_op = Bool_ptr->op;
			if(Bool_op == Or_op)
				printf("Bool Expression: OR \n");
			else if(Bool_op == And_op)
				printf("Bool Expression: AND \n");
			else if(Bool_op == Not_op)
				printf("Bool Expression: NOT \n");
			break;
		default: /* wrong choice case */
			printf("Error in node selection!\n");
	}
}


void ast_traversal(AST_Node *node){
	if(node == NULL)
		return;

	/* temp nodes */
	AST_List *List_ptr;
	// AST_DeclarationList *DeclList_ptr;
	AST_Declaration *Decl_ptr;
	// AST_IdentifierList *IdList_ptr;
	AST_Id *Id_ptr;
	AST_var *Var_ptr;
	AST_ArraySize *Arrsize_ptr;
	AST_Arrayidx *Arridx_ptr;
	AST_Const *Const_ptr;
	AST_Type *Type_ptr;
	// AST_SubprogramDeclarationList *SubProgDeclList_ptr;
	AST_SubprogramDeclaration *SubProgDecl_ptr;
	AST_SubprogramHead *SubProgHead_ptr;
	AST_Arguments *Arguments_ptr;
	// AST_ParameterList *ParamList_ptr;
	AST_Params *Params_ptr;
	AST_CompoundStatment_node *CompStmt_ptr;
	// AST_StatementList *StmtList_ptr;
	AST_Assignment *Assignment_ptr;
	AST_ProcedureStatement *ProcedureStmt_ptr;
	AST_ifelse *Ifelse_ptr;
	AST_while *While_ptr;
	// AST_ExpressionList *ExprList_ptr;
	AST_Expression *Expr_ptr;
	AST_operator_expr *op_ptr;
	// AST_arithm *Arithm_ptr;
	// AST_relation *Relation_ptr;
	// AST_bool *Bool_ptr;

	int node_type = node->type;
	
	// list node
	if(	   node_type==DECL_LIST 
		|| node_type==ID_LIST 
		|| node_type ==SubProgDecl_LIST 
		|| node_type ==PARAM_LIST 
		|| node_type ==STMT_LIST 
		|| node_type== EXPR_LIST) 
	{
		ast_print_node(node);

		List_ptr = (AST_List *)node;
		ast_traversal(List_ptr->children);
	} 
	else if(node_type==DECL) {
		ast_print_node(node);

		Decl_ptr = (AST_Declaration *)node;
		ast_traversal(Decl_ptr->idList);
		ast_traversal(Decl_ptr->Type_node);

		ast_traversal(Decl_ptr->next);
	}
	else if(node_type==ID_NODE){
		ast_print_node(node);
		
		Id_ptr = (AST_Id *)node;

		ast_traversal(Id_ptr->next);	
	}
	else if(node_type==VAR_NODE){
		ast_print_node(node);

		Var_ptr =(AST_var *)node;
		ast_traversal(Var_ptr->arrayidx);
	}
	else if(node_type==ARRAYSIZE){
		ast_print_node(node);

		Arrsize_ptr =(AST_ArraySize *)node;
		ast_traversal(Arrsize_ptr->next);
	}
	else if(node_type==ARRIDX){
		ast_print_node(node);

		Arridx_ptr =(AST_Arrayidx *)node;
		ast_traversal(Arridx_ptr->expr);

		ast_traversal(Arridx_ptr->next);
	}
	else if(node_type==CONST_NODE){
		ast_print_node(node);
	}
	else if(node_type==TYPE_NODE){
		ast_print_node(node);

		Type_ptr = (AST_Type *)node;
		ast_traversal(Type_ptr->children);
	}
	else if(node_type==SubProgDecl){
		ast_print_node(node);

		SubProgDecl_ptr =(AST_SubprogramDeclaration *)node;
		ast_traversal(SubProgDecl_ptr->head);
		ast_traversal(SubProgDecl_ptr->declList);
		ast_traversal(SubProgDecl_ptr->compstmt);

		ast_traversal(SubProgDecl_ptr->next);
	}
	else if(node_type==SubProgHead){
		ast_print_node(node);

		SubProgHead_ptr =(AST_SubprogramHead *)node;
		ast_traversal(SubProgHead_ptr->id);
		ast_traversal(SubProgHead_ptr->arguments);
	}
	else if(node_type==ARGUMENTS){
		ast_print_node(node);

		Arguments_ptr =(AST_Arguments *)node;
		ast_traversal(Arguments_ptr->paramList);
	}
	else if(node_type==PARAMS){
		ast_print_node(node);

		Params_ptr =(AST_Params *)node;
		ast_traversal(Params_ptr->idList);
		ast_traversal(Params_ptr->Type_node);

		ast_traversal(Params_ptr->next);
	}
	else if(node_type==COMPSTMT){
		ast_print_node(node);

		CompStmt_ptr =(AST_CompoundStatment_node *)node;
		ast_traversal(CompStmt_ptr->stmtList);

		ast_traversal(CompStmt_ptr->next);
	}
	else if(node_type==ASSIGN_NODE){
		ast_print_node(node);

		Assignment_ptr =(AST_Assignment *)node;
		ast_traversal(Assignment_ptr->variable);
		ast_traversal(Assignment_ptr->expr);

		ast_traversal(Assignment_ptr->next);
	}
	else if(node_type==FUNC_CALL){
		ast_print_node(node);

		ProcedureStmt_ptr =(AST_ProcedureStatement *)node;
		ast_traversal(ProcedureStmt_ptr->id);
		ast_traversal(ProcedureStmt_ptr->exprList);

		ast_traversal(ProcedureStmt_ptr->next);
	}
	else if(node_type==IFELSE_NODE){
		ast_print_node(node);

		Ifelse_ptr =(AST_ifelse *)node;
		ast_traversal(Ifelse_ptr->expr);
		ast_traversal(Ifelse_ptr->ifstmt);
		ast_traversal(Ifelse_ptr->elsestmt);

		ast_traversal(Ifelse_ptr->next);
	}
	else if(node_type==WHILE_NODE){
		ast_print_node(node);

		While_ptr =(AST_while *)node;
		ast_traversal(While_ptr->expr);
		ast_traversal(While_ptr->stmt);

		ast_traversal(While_ptr->next);
	}
	else if(node_type==EXPR){
		ast_print_node(node);

		Expr_ptr =(AST_Expression *)node;
		ast_traversal(Expr_ptr->subExpr);

		ast_traversal(Expr_ptr->next);
	}
	else if(	node_type==ARITHM_NODE 
				|| node_type==REL_NODE 
				|| node_type==BOOL_NODE)
	{
		ast_print_node(node);

		op_ptr =(AST_operator_expr *)node;
		ast_traversal(op_ptr->Lexpr);
		ast_traversal(op_ptr->Rexpr);

		ast_traversal(op_ptr->next);
	}

	/* others */
	else{
		ast_print_node(node);
	}
}


#endif
