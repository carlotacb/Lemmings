#ifndef _SCROLLER_INCLUDE
#define _SCROLLER_INCLUDE


class Scroller
{

public:
	static Scroller &getInstance()
	{
		static Scroller instance; // Guaranteed to be destroyed.
							   // Instantiated on first use.
		return instance;
	};

	void scrollLeft();
	void scrollRight();
	bool isScrolled();
	void iScroll();

private:
	void scroll(int scrollDisplacement);
	bool scrolled;
};

#endif // _SCROLLER_INCLUDE


