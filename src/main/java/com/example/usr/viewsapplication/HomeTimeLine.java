package com.example.usr.viewsapplication;

import android.os.Bundle;
import android.os.Handler;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AppCompatActivity;
import android.widget.ListView;

import com.twitter.sdk.android.Twitter;
import com.twitter.sdk.android.core.Callback;
import com.twitter.sdk.android.core.Result;
import com.twitter.sdk.android.core.TwitterException;
import com.twitter.sdk.android.core.models.Tweet;
import com.twitter.sdk.android.core.services.StatusesService;
import com.twitter.sdk.android.tweetui.FixedTweetTimeline;
import com.twitter.sdk.android.tweetui.TweetTimelineListAdapter;

import java.util.List;

import retrofit2.Call;

public class HomeTimeLine extends AppCompatActivity implements SwipeRefreshLayout.OnRefreshListener {

    TweetTimelineListAdapter adapter;
    SwipeRefreshLayout swipeHome;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_time_line);

        final StatusesService statusesService = Twitter.getApiClient().getStatusesService();
        Call<List<Tweet>> list = statusesService
                .homeTimeline(800, null, null, false, false, false, null);
        list.enqueue(new Callback<List<Tweet>>() {
            @Override
            public void success(Result<List<Tweet>> result) {
                final FixedTweetTimeline userTimeline = new FixedTweetTimeline.Builder()
                        .setTweets(result.data)
                        .build();
                adapter = new TweetTimelineListAdapter.Builder(HomeTimeLine.this)
                        .setTimeline(userTimeline)
                        .setViewStyle(R.style.tw__TweetDarkWithActionsStyle)
                        .build();
                ListView lv = (ListView) findViewById(R.id.list_home);
                lv.setAdapter(adapter);
            }

            @Override
            public void failure(TwitterException exception) {
            }


        });

        swipeHome = (SwipeRefreshLayout) findViewById(R.id.swipe_home);
        swipeHome.setOnRefreshListener(this);
    }

    @Override
    public void onRefresh() {
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                HomeTimeLine.this.recreate();
                swipeHome.setRefreshing(false);
            }
        }, 500);
    }
}
