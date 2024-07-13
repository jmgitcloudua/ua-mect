package com.example.ihc_2122.money;

public class Budget {
    private final String name;
    private final float total;
    private final float spent;
    private final String description;

    public Budget(String name, float total, float spent, String description) {
        this.name = name;
        this.total = total;
        this.spent = spent;
        this.description = description;
    }

    public String getName() {
        return name;
    }

    public float getTotal() {
        return total;
    }

    public float getSpent() {
        return spent;
    }

    public String getDescription() {
        return description;
    }
}
