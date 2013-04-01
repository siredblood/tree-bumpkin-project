#ifndef DELAY_REDRAW
#define DELAY_REDRAW

/**
 * A helper class that allows scoped disabling of updates
 */
class DelayRedraw
{
public:
	DelayRedraw( CWnd* wnd );
	~DelayRedraw();
private:
	CWnd* wnd_;
	static std::map< CWnd*, int > s_counter_;
};

#endif // DELAY_REDRAW