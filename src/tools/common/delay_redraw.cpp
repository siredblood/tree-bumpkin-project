#include "pch.hpp"
#include "delay_redraw.hpp"

std::map< CWnd*, int > DelayRedraw::s_counter_;

DelayRedraw::DelayRedraw( CWnd* wnd ):
	wnd_(wnd)
{
	if (s_counter_[wnd_]++ == 0)
	{
		wnd_->SetRedraw( FALSE );
	}
}

DelayRedraw::~DelayRedraw()
{
	if (--s_counter_[wnd_] <= 0)
	{
		wnd_->SetRedraw( TRUE );
		wnd_->Invalidate(); 
	}
}
