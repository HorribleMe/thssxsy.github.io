package com.example.thss_xsy.myapplication;

/**
 * Created by THSS-XSY on 2018/2/4.
 */
import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Point;
import android.os.Bundle;
import android.os.Handler;
import android.view.Display;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.graphics.Color;
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;
import android.graphics.Canvas;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.ColorFilter;
import android.graphics.Paint;

import java.util.Timer;
import java.util.TimerTask;

public class Trans extends Activity {
    private Bitmap bitmap;
    private int height, width;
    private int pieceWidth;
    private int pieceHeight;
    Activity activity;
    static String path;
    String data;
    int presentState;
    Bitmap picture;
    Bitmap _picture;
    ImageView pictureForTrans;
    int partHeight;
    Point size;
    double[][] Light;
    Timer timer;
    TimerTask timerTask;
    final Handler handler = new Handler();
    private static int timeInt = 400;
    private static String TAG = "Trans";
    RelativeLayout.LayoutParams params;
    RelativeLayout layout;
    boolean transOver;

    List<ImagePiece> mItemBitmaps;
    List<ImagePiece> imagePieces = new ArrayList<ImagePiece>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        activity = this;

        presentState = 0;
        Bundle extras = getIntent().getExtras();
        if (extras != null) {
            path = extras.getString("path");
            data = extras.getString("data");
        }
        data = "1010101010101010101010101010";
        //data = "0000000000000000000000000000000000000000000000000";
        //data = "111111111111111111111111111111111111111111111111111";
        transOver = false;
        setContentView(R.layout.showpicture);
        layout = (RelativeLayout) findViewById(R.id.mainLayout);
        params = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.MATCH_PARENT);
        picture = BitmapFactory.decodeFile(path);
        width = picture.getWidth();
        height = picture.getHeight();
        _picture = Bitmap.createBitmap(width , height, Bitmap.Config.ARGB_8888);

        mItemBitmaps = ImageSplitterUtil.splitImage(picture, 3);

        Canvas cv = new Canvas(_picture);
        pieceWidth = width / 3;
        pieceHeight = height / 3;
        int w2 = 0;
        int h2 = 0;

        for (int s = 0; s < mItemBitmaps.size(); s++) {

            Bitmap tempBitmap = mItemBitmaps.get(s).getBitmap();
            ImagePiece imagePiece = new ImagePiece();
            imagePiece.setBitmap(brighter(tempBitmap));

            imagePieces.add(imagePiece);
        }

        for (int i = 0; i < imagePieces.size(); i++) {
            if (i == 3 || i == 6) {
                w2 = w2 + pieceWidth - 2;
                h2 = 0;
            } else if (i != 0) {
                h2 += pieceHeight - 2;
            }
            cv.drawBitmap(imagePieces.get(i).getBitmap(), w2, h2, null);
            cv.save(Canvas.ALL_SAVE_FLAG);
            cv.restore();
        }
        pictureForTrans = new ImageView(this);
        pictureForTrans.setImageBitmap(_picture);
        pictureForTrans.setLayoutParams(params);
        layout.addView(pictureForTrans);

        startTimer();

    }

    private void getPictureLight() {
        int width = size.x;
        int height = size.y;
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

    private Bitmap brighter(Bitmap piece) {
        Bitmap newPiece = Bitmap.createBitmap(piece.getWidth(), piece.getHeight(), Bitmap.Config.ARGB_8888);
        Canvas cv = new Canvas(newPiece);
        ColorMatrix cMatrix = new ColorMatrix();
        Paint mPaint = new Paint();
        cMatrix.set(new float[] { 1, 0, 0, 0, 30, 0, 1, 0, 0,
                30,// 改变亮度
                0, 0, 1, 0, 30, 0, 0, 0, 1, 0 });
        mPaint.setColorFilter(new ColorMatrixColorFilter(cMatrix));
        cv.drawBitmap(piece, 0, 0, mPaint);
        return newPiece;
    }

    private Bitmap darker(Bitmap piece) {
        Bitmap newPiece = Bitmap.createBitmap(piece.getWidth(), piece.getHeight(), Bitmap.Config.ARGB_8888);
        Canvas cv = new Canvas(newPiece);
        ColorMatrix cMatrix = new ColorMatrix();
        Paint mPaint = new Paint();
        cMatrix.set(new float[] { 1, 0, 0, 0, -30, 0, 1, 0, 0,
                -30,// 改变亮度
                0, 0, 1, 0, -30, 0, 0, 0, 1, 0 });
        mPaint.setColorFilter(new ColorMatrixColorFilter(cMatrix));
        cv.drawBitmap(piece, 0, 0, mPaint);
        return newPiece;
    }

    private void refresh()
    {
        Iterator it = imagePieces.iterator();
        while (it.hasNext())
        {
            it.next();
            if(true)
                it.remove();
        }

    }

    private void setFirstState()
    {
        for (int s = 0; s < mItemBitmaps.size(); s++) {

            Bitmap tempBitmap = mItemBitmaps.get(s).getBitmap();
            ImagePiece imagePiece = new ImagePiece();
            imagePiece.setBitmap(brighter(tempBitmap));

            imagePieces.add(imagePiece);
        }
    }


    public void startTimer() {
        timer = new Timer();
        initializeTimerTask();
        timer.schedule(timerTask, 500, timeInt);
    }

    public void initializeTimerTask() {
        timerTask = new TimerTask() {
            @Override
            public void run() {
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        refresh();
                        Canvas cv = new Canvas(_picture);
                        int w2 = 0;
                        int h2 = 0;
                        if(transOver == true)
                        {
                            setFirstState();
                            presentState = 0;
                            transOver = false;

                            for (int i = 0; i < imagePieces.size(); i++) {
                                if (i == 3 || i == 6) {
                                    w2 = w2 + pieceWidth - 2;
                                    h2 = 0;
                                } else if (i != 0) {
                                    h2 += pieceHeight - 2;
                                }
                                cv.drawBitmap(imagePieces.get(i).getBitmap(), w2, h2, null);
                                cv.save(Canvas.ALL_SAVE_FLAG);
                                cv.restore();
                            }
                        }
                        else {
                            for (int i = 0; i < mItemBitmaps.size(); i++) {
                                Bitmap tempBitmap = mItemBitmaps.get(i).getBitmap();
                                ImagePiece imagePiece = new ImagePiece();

                                if(transOver == false) {
                                    if (data.charAt(presentState) == '1')
                                        imagePiece.setBitmap(brighter(tempBitmap));
                                    else
                                        imagePiece.setBitmap(darker(tempBitmap));
                                }
                                else
                                {
                                    imagePiece.setBitmap(darker(tempBitmap));
                                }
                                presentState++;
                                if(presentState >= data.length())
                                    transOver = true;
                                imagePieces.add(imagePiece);
                            }

                            for (int i = 0; i < imagePieces.size(); i++) {
                                if (i == 3 || i == 6) {
                                    w2 = w2 + pieceWidth - 2;
                                    h2 = 0;
                                } else if (i != 0) {
                                    h2 += pieceHeight - 2;
                                }
                                cv.drawBitmap(imagePieces.get(i).getBitmap(), w2, h2, null);
                                cv.save(Canvas.ALL_SAVE_FLAG);
                                cv.restore();
                            }
                        }
                        pictureForTrans.setImageBitmap(_picture);
                        pictureForTrans.setLayoutParams(params);
                    }
                });
            }
        };
    }

}


