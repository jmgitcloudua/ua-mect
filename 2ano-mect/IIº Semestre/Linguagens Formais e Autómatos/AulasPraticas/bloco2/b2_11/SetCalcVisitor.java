// Generated from SetCalc.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link SetCalcParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface SetCalcVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link SetCalcParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(SetCalcParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link SetCalcParser#line}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLine(SetCalcParser.LineContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ExprParentesis}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprParentesis(SetCalcParser.ExprParentesisContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ExprDiference}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprDiference(SetCalcParser.ExprDiferenceContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ExprUnion}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprUnion(SetCalcParser.ExprUnionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ExprIntersection}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprIntersection(SetCalcParser.ExprIntersectionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ExprAssignment}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprAssignment(SetCalcParser.ExprAssignmentContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ExprID}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprID(SetCalcParser.ExprIDContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ExprSet}
	 * labeled alternative in {@link SetCalcParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprSet(SetCalcParser.ExprSetContext ctx);
	/**
	 * Visit a parse tree produced by {@link SetCalcParser#assignment}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignment(SetCalcParser.AssignmentContext ctx);
	/**
	 * Visit a parse tree produced by {@link SetCalcParser#set}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSet(SetCalcParser.SetContext ctx);
}