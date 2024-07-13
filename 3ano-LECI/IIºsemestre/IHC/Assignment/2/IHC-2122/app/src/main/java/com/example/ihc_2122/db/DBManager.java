package com.example.ihc_2122.db;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteConstraintException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import com.example.ihc_2122.money.Budget;
import com.example.ihc_2122.money.Expense;

import java.util.ArrayList;
import java.util.List;

public class DBManager extends SQLiteOpenHelper {
    public DBManager(Context ctx) {
        super(ctx, "testName", null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        // Reset database
        db.execSQL("DROP TABLE IF EXISTS budget");
        db.execSQL("DROP TABLE IF EXISTS expense");

        // Queries to create the tables
        db.execSQL("CREATE TABLE IF NOT EXISTS budget (" +
                "name varchar(20) primary key," +
                "total float NOT NULL," +
                "description text NOT NULL" +
                ")"
        );
        db.execSQL("CREATE TABLE IF NOT EXISTS expense (" +
                "id int PRIMARY KEY AUTOINCREMENT," +
                "name varchar(20) NOT NULL," +
                "cost float NOT NULL," +
                "budget varchar(20) NOT NULL REFERENCES budget(name)," +
                "description text NOT NULL" +
                ")"
        );

        // populate database with dummy data
        try {
            db.execSQL("INSERT INTO budget VALUES " +
                    "(0, 'comida', 50.0, '')," +
                    "(0, 'transportes', 100.0, '')," +
                    "(0, 'social', 30.0, '')" +
                    ";"
            );
            db.execSQL("INSERT INTO expense VALUES " +
                    "('café', 0.60, 'comida', '')," +
                    "('jantar', 10.0, 'comida', '')," +
                    "('saída', 5.0, 'social', '')" +
                    ";"
            );
        } catch (SQLiteConstraintException ignored) {
        }
    }

    public Budget getBudget(String name) {
        final SQLiteDatabase db = getReadableDatabase();

        final Cursor c = db.rawQuery(
                "SELECT name, total, sum(expense.cost) " +
                        "FROM budget JOIN expense ON (budget.name = expense.budget)" +
                        "WHERE name=" + name + " " +
                        "GROUP BY expense.budget" +
                        ";",
                null);
        c.moveToNext();
        final Budget res = new Budget(c.getString(0), c.getFloat(1), c.getFloat(2), c.getString(3));
        c.close();
        return res;
    }

    public void storeExpense(Expense expense) {
        final SQLiteDatabase db = getWritableDatabase();

        db.execSQL("INSERT INTO expenses VALUES " +
                "(0, " +
                "'" + expense.getName() + "', " +
                "" + expense.getCost() + ", " +
                "'" + expense.getBudget() + "')," +
                "'" + expense.getDescription() + "')," +
                ";"
        );
    }

    public void storeBudget(Budget budget) {
        final SQLiteDatabase db = getWritableDatabase();

        db.execSQL("INSERT INTO budgets VALUES " +
                "(0, " +
                "'" + budget.getName() + "', " +
                "" + budget.getTotal() + ", " +
                "'" + budget.getDescription() + "')," +
                ";"
        );
    }

    public List<Expense> getExpenses() {
        final SQLiteDatabase db = getReadableDatabase();

        final Cursor c = db.rawQuery(
                "SELECT * FROM expense;",
                null);

        final List<Expense> bs = new ArrayList<>();
        while (c.moveToNext())
            bs.add(new Expense(c.getString(0), c.getFloat(1), c.getString(2), c.getString(3)));
        c.close();
        return bs;
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int i, int i1) {
        // Reset database
        db.execSQL("DROP TABLE IF EXISTS budget");
        db.execSQL("DROP TABLE IF EXISTS expense");

        onCreate(db);
    }
}
