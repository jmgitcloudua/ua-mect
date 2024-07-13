package com.example.ihc_2122.money;

public class Expense {
    private final String name;
    private final float cost;
    private final String budget;
    private final String description;

    public Expense(String name, float cost, String budget, String description) {
        this.name = name;
        this.cost = cost;
        this.budget = budget;
        this.description = description;
    }

    public String getName() {
        return name;
    }

    public float getCost() {
        return cost;
    }

    public String getDescription() {
        return description;
    }

    public String getBudget() {
        return budget;
    }
}
