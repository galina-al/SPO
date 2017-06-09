package com.example.usr.viewsapplication;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Gravity;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.squareup.picasso.Picasso;
import com.twitter.sdk.android.core.TwitterCore;
import com.twitter.sdk.android.core.TwitterSession;
import com.twitter.sdk.android.tweetcomposer.ComposerActivity;

import static android.R.drawable.ic_dialog_email;


public class MainActivity extends AppCompatActivity  {

    private ImageView ivUserProfileImg;
    private ImageView ivUserProfileBGImg;
    private TextView txtUserScreenName;
    private TextView txtUserTagLine;
    private TextView txtFollowersCount;
    private TextView txtFollowingCount;
    private TextView txtTweetCount;
    private Bundle extras;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        FloatingActionButton add_tweet_btn = new FloatingActionButton.Builder(this)
                .withDrawable(getResources().getDrawable(ic_dialog_email))
                .withButtonColor(Color.parseColor("#098f79"))
                .withGravity(Gravity.BOTTOM | Gravity.RIGHT)
                .withMargins(0, 0, 16, 16)
                .create();


        FloatingActionButton search_btn = new FloatingActionButton.Builder(this)
                .withDrawable(getResources().getDrawable(R.drawable.ic_search))
                .withButtonColor(Color.parseColor("#098f79"))
                .withGravity(Gravity.BOTTOM | Gravity.RIGHT)
                .withMargins(0, 0, 16, 80)
                .create();

        FloatingActionButton home_btn = new FloatingActionButton.Builder(this)
                .withDrawable(getResources().getDrawable(R.drawable.ic_account_balance))
                .withButtonColor(Color.parseColor("#098f79"))
                .withGravity(Gravity.BOTTOM | Gravity.RIGHT)
                .withMargins(0, 0, 16, 150)
                .create();

        getInfo();

        TimeLineFragment timeLineFragment = new TimeLineFragment();
        timeLineFragment.setArguments(extras);
        getSupportFragmentManager()
                .beginTransaction()
                .replace(R.id.root_container, timeLineFragment)
                .commit();

        add_tweet_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                final TwitterSession session = TwitterCore.getInstance().getSessionManager()
                        .getActiveSession();
                final Intent intent1 = new ComposerActivity.Builder(MainActivity.this)
                        .session(session)
                        .darkTheme()
                        .hashtags("#twitter")
                        .createIntent();
                startActivity(intent1);
            }
        });
        search_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
               Intent intent = new Intent(MainActivity.this, SearchActivity.class);
                startActivity(intent);
            }
        });

        home_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, HomeTimeLine.class);
                startActivity(intent);
            }
        });

    }

    public void getInfo(){
        extras = getIntent().getExtras();
        String userName = extras.getString(Const.USER_NAME);
        String screenName = extras.getString(Const.SCREEN_NAME);
        String userId = extras.getString(Const.USER_ID);
        String followersCount = extras.getString(Const.FOLLOWERS_COUNT);
        String followingCount = extras.getString(Const.FOLLOWING_COUNT);
        String tweetCount = extras.getString(Const.TWEET_COUNT);
        String profileImgUrl = extras.getString(Const.PROFILE_IMG_URL);
        String profileImgBgUrl = extras.getString(Const.PROFILE_IMG_BG_URL);

        txtUserScreenName = (TextView) findViewById(R.id.txtUserScreenName);
        txtUserScreenName.setText(userName);

        txtUserTagLine = (TextView) findViewById(R.id.txtUserTagLine);
        txtUserTagLine.setText("@" + screenName);

        txtFollowersCount = (TextView) findViewById(R.id.txtFollowersCount);
        txtFollowersCount.setText(followersCount);

        txtFollowingCount = (TextView) findViewById(R.id.txtFollowingCount);
        txtFollowingCount.setText(followingCount);

        txtTweetCount = (TextView) findViewById(R.id.txtTweetCount);
        txtTweetCount.setText(tweetCount);

        ivUserProfileImg = (ImageView) findViewById(R.id.ivUserProfileImg);
        Picasso.with(getApplicationContext()).load(profileImgUrl).into(ivUserProfileImg);

        ivUserProfileBGImg = (ImageView) findViewById(R.id.ivUserProfileBGImg);
        Picasso.with(getApplicationContext()).load(profileImgBgUrl).into(ivUserProfileBGImg);

    }
}
