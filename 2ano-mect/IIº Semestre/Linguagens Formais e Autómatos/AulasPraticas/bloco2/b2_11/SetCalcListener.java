// Generated from SetCalc.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link SetCalcParser}.
 */
public interface SetCalcListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link SetCalcParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(SetCalcParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link SetCalcParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(SetCalcParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link SetCalcParser#line}.
	 * @param ctx the parse tree
	 */
	void enterLine(SetCalcParser.LineContext ctx);
	/**
	 * Exit a parse tree produced by {@link SetCalcParser#line}.
	 * @param ctx the parse tree
	 */
	void exitLine(SetCalcParser.LineContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprParentesis}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExprParentesis(SetCalcParser.ExprParentesisContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprParentesis}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExprParentesis(SetCalcParser.ExprParentesisContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprDiference}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExprDiference(SetCalcParser.ExprDiferenceContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprDiference}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExprDiference(SetCalcParser.ExprDiferenceContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprUnion}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExprUnion(SetCalcParser.ExprUnionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprUnion}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExprUnion(SetCalcParser.ExprUnionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprIntersection}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExprIntersection(SetCalcParser.ExprIntersectionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprIntersection}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExprIntersection(SetCalcParser.ExprIntersectionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprAssignment}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExprAssignment(SetCalcParser.ExprAssignmentContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprAssignment}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExprAssignment(SetCalcParser.ExprAssignmentContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprID}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExprID(SetCalcParser.ExprIDContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprID}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExprID(SetCalcParser.ExprIDContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExprSet}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExprSet(SetCalcParser.ExprSetContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExprSet}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExprSet(SetCalcParser.ExprSetContext ctx);
	/**
	 * Enter a parse tree produced by {@link SetCalcParser#assignment}.
	 * @param ctx the parse tree
	 */
	void enterAssignment(SetCalcParser.AssignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link SetCalcParser#assignment}.
	 * @param ctx the parse tree
	 */
	void exitAssignment(SetCalcParser.AssignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link SetCalcParser#set}.
	 * @param ctx the parse tree
	 */
	void enterSet(SetCalcParser.SetContext ctx);
	/**
	 * Exit a parse tree produced by {@link SetCalcParser#set}.
	 * @param ctx the parse tree
	 */
	void exitSet(SetCalcParser.SetContext ctx);
}