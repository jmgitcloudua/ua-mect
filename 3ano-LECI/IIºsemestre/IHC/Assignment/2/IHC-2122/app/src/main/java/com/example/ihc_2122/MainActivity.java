package com.example.ihc_2122;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.example.ihc_2122.db.DBManager;
import com.example.ihc_2122.money.Budget;
import com.example.ihc_2122.views.CustomPieChart;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private final DBManager dbManager = new DBManager(this);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final CustomPieChart chart = findViewById(R.id.piechart);
        final List<Budget> budgets = new ArrayList<>();
        budgets.add(new Budget("A", 100.0f, 33.3f, "description"));
        budgets.add(new Budget("B", 50.0f, 25f, "description 2"));
        budgets.add(new Budget("C", 100.0f, 200f, "description C"));

        chart.loadBudgets(budgets);
        chart.startAnimation();

//        System.out.println("ALL DONE!");
    }
}