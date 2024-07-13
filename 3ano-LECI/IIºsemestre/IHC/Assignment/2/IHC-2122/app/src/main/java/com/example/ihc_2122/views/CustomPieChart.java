package com.example.ihc_2122.views;

import android.content.Context;
import android.graphics.Color;
import android.util.AttributeSet;

import com.example.ihc_2122.money.Budget;

import org.eazegraph.lib.charts.PieChart;
import org.eazegraph.lib.models.PieModel;

import java.util.List;

public class CustomPieChart extends PieChart {
    public CustomPieChart(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public void loadBudgets(List<Budget> budgets) {
        for (Budget b : budgets) {
            PieModel sl1 = new PieModel(
                    b.getName(),
                    b.getSpent() < b.getTotal() ? b.getSpent() : b.getTotal(),
                    b.getSpent() < b.getTotal() ? Color.GREEN : Color.RED
            );
            sl1.setShowLabel(true);
            addPieSlice(sl1);

            PieModel sl2 = new PieModel(
                    "",
                    b.getSpent() < b.getTotal() ? b.getTotal() - b.getSpent() : b.getSpent() - b.getTotal(),
                    b.getSpent() < b.getTotal() ? Color.GRAY : Color.MAGENTA
            );
            addPieSlice(sl2);

            System.out.println("Labels: " + sl1.canShowLabel() + " " + sl1.getLegendLabel());
            System.out.println("Labels: " + sl2.canShowLabel() + " " + sl2.getLegendLabel());
        }
    }
}
