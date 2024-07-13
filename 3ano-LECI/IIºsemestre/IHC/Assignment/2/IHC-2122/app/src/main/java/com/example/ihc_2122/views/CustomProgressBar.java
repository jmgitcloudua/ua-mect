package com.example.ihc_2122.views;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.view.View;

import com.example.ihc_2122.R;

public class CustomProgressBar extends View {

    private final TypedArray typedArray;

    private final Rect rectangle;
    private final Paint paint;

    public CustomProgressBar(Context context, AttributeSet attr) {
        super(context, attr);
        int x = 50;
        int y = 50;
        int sideLength = 200;

        // create a rectangle that we'll draw later
        rectangle = new Rect(x, y, sideLength, sideLength);

        typedArray = context.obtainStyledAttributes(attr, R.styleable.CustomProgressBar);

        // create the Paint and set its color
        paint = new Paint();
        final float percent = typedArray.getFloat(R.styleable.CustomProgressBar_percentage, 0);
        paint.setColor(percent < 0.5 ? Color.GREEN : Color.RED);
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        System.out.println("MEASURES: " + widthMeasureSpec + " " + heightMeasureSpec);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        final int width = getWidth();
        final int height = getHeight();
        final float percent = typedArray.getFloat(R.styleable.CustomProgressBar_percentage, 0);

        rectangle.set(0, 0, (int) (width * percent), height);

        canvas.drawColor(Color.GRAY);
        canvas.drawRect(rectangle, paint);

        typedArray.recycle();
    }

}
