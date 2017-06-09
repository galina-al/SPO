package com.example.usr.viewsapplication;

import android.os.Bundle;
import android.support.v4.app.ListFragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.twitter.sdk.android.core.Callback;
import com.twitter.sdk.android.core.Result;
import com.twitter.sdk.android.core.TwitterException;
import com.twitter.sdk.android.core.models.Tweet;
import com.twitter.sdk.android.tweetui.SearchTimeline;
import com.twitter.sdk.android.tweetui.TimelineResult;
import com.twitter.sdk.android.tweetui.TweetTimelineListAdapter;


public class SearchTimeLineFragment extends ListFragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.timeline_fragment, container, false);

        final TweetTimelineListAdapter adapter = searchTimeLine();

        final SwipeRefreshLayout swipeLayout = (SwipeRefreshLayout) rootView.findViewById(R.id.swipe_layout);
        swipeLayout.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                swipeLayout.setRefreshing(true);
                adapter.refresh(new Callback<TimelineResult<com.twitter.sdk.android.core.models.Tweet>>() {
                    @Override
                    public void success(Result<TimelineResult<Tweet>> result) {
                        swipeLayout.setRefreshing(false);
                    }

                    @Override
                    public void failure(TwitterException exception) {
                        Toast.makeText(getActivity().getApplicationContext(), "Failed to retrieve timeline",Toast.LENGTH_LONG);
                    }
                });
            }
        });
        return rootView;
    }

    public TweetTimelineListAdapter searchTimeLine(){
        String searchText = getArguments().getString(Const.SEARCH_TEXT);
        SearchTimeline searchTimeline = new SearchTimeline.Builder()
                .query(searchText)
                .build();

        final TweetTimelineListAdapter adapter = new TweetTimelineListAdapter.Builder(getActivity())
                .setTimeline(searchTimeline)
                .setViewStyle(R.style.tw__TweetDarkWithActionsStyle)
                .build();
        setListAdapter(adapter);
        return adapter;
    }


}