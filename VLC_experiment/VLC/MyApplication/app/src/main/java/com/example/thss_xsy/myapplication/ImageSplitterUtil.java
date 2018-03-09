package com.example.thss_xsy.myapplication;

import java.util.ArrayList;
import java.util.List;
import android.graphics.Bitmap;
/**
 * Created by THSS-XSY on 2018/2/4.
 */

public class ImageSplitterUtil {
    public static List<ImagePiece> splitImage(Bitmap bitmap, int piece)
    {
        List<ImagePiece> imagePieces = new ArrayList<ImagePiece>();

        int width = bitmap.getWidth();
        int height = bitmap.getHeight();

        int pieceWidth = width / piece;
        int pieceHeight = height / piece;

        for (int i = 0; i < piece; i++){
            for (int j = 0; j < piece; j++){
                ImagePiece imagePiece = new ImagePiece();

                int x = i * pieceWidth;
                int y = j * pieceHeight;

                imagePiece.setBitmap(Bitmap.createBitmap(bitmap, x, y,
                        pieceWidth, pieceHeight));
                imagePieces.add(imagePiece);
            }
        }
        return imagePieces;
    }
}
