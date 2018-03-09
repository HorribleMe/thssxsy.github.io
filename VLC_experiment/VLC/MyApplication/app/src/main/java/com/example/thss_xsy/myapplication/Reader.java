package com.example.thss_xsy.myapplication;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.EditText;

/**
 * Created by THSS-XSY on 2018/2/4.
 */

public class Reader extends Activity {
    Activity activity;
    static String path;
    Bitmap picture;
    private int height, width;
    private int pieceWidth;
    private int pieceHeight;
    double[][] Light;
    double[][] LightAverage;
    double flag;
    char[] info;
    private EditText information;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        activity = this;
        information = (EditText) findViewById(R.id.information);
        flag = 30;
        Bundle extras = getIntent().getExtras();
        if (extras != null) {
            path = extras.getString("path");
        }
        picture = BitmapFactory.decodeFile(path);
        width = picture.getWidth();
        height = picture.getHeight();
        Light = new double[width][height];
        LightAverage = new double[3][3];
        pieceWidth = width / 3;
        pieceHeight = height / 3;
        getPictureLight();
        getAverageLight();
        //double LightForOne[][] = {{52, 86, 97}, {81, 119, 113}, {77, 138, 96}};
        //double LightForOne[][] = {{119, 137, 142}, {144, 160, 151}, {142, 177, 141}};
        double LightForOne[][] = {{105, 126, 131}, {133, 157, 145}, {126, 170, 132}};
        info = new char[9];
        getInfo(LightForOne);
        String tem = new String(info);
        information.setText(tem);
        return;
    }

    private void getPictureLight() {
        int r, g, b;
        Integer localTemp;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                localTemp = (Integer) picture.getPixel(i, j);
                r = (localTemp | 0xff00ffff) >> 16 & 0x00ff;
                g = (localTemp | 0xffff00ff) >> 8 & 0x0000ff;
                b = (localTemp | 0xffffff00) & 0x0000ff;

                Light[i][j] = 0.299 * r + 0.587 * g + 0.114 * b;
            }
        }
    }

    private void getAverageLight() {
        int x = 0;
        int y = 0;
        double tem;
        for(int i = 0;i < 9;i++)
        {
            tem = 0;
            for(int m = (pieceWidth * x);m < (pieceWidth * (x + 1));m++)
            {
                for(int n = (pieceHeight * y);n < (pieceHeight * (y + 1));n++) {
                    tem = tem + Light[m][n];
                }
            }
            LightAverage[x][y] = tem / (pieceHeight * pieceWidth);
            if(i == 2 || i == 5)
            {
                y++;
                x = 0;
            }
            else
                x++;
        }
    }

    private void getInfo(double LightForOne[][])
    {
        int count = 0;
        for(int i = 0;i < 3;i++)
        {
            for(int j = 0;j < 3;j++)
            {
                if(LightAverage[i][j] >= (LightForOne[i][j] - flag))
                    info[count] = '1';
                else
                    info[count] = '0';
                count++;
            }
        }
    }
}
