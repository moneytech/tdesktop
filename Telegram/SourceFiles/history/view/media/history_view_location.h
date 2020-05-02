/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "history/view/media/history_view_media.h"

namespace Data {
struct LocationThumbnail;
} // namespace Data

namespace HistoryView {

class Location : public Media {
public:
	Location(
		not_null<Element*> parent,
		not_null<Data::LocationThumbnail*> location,
		const QString &title = QString(),
		const QString &description = QString());

	void draw(Painter &p, const QRect &r, TextSelection selection, crl::time ms) const override;
	TextState textState(QPoint point, StateRequest request) const override;

	[[nodiscard]] TextSelection adjustSelection(
		TextSelection selection,
		TextSelectType type) const override;
	uint16 fullSelectionLength() const override {
		return _title.length() + _description.length();
	}
	bool hasTextForCopy() const override {
		return !_title.isEmpty() || !_description.isEmpty();
	}

	bool toggleSelectionByHandlerClick(const ClickHandlerPtr &p) const override {
		return p == _link;
	}
	bool dragItemByHandler(const ClickHandlerPtr &p) const override {
		return p == _link;
	}

	TextForMimeData selectedText(TextSelection selection) const override;

	bool needsBubble() const override;
	bool customInfoLayout() const override {
		return true;
	}

	bool skipBubbleTail() const override {
		return isBubbleBottom();
	}

private:
	QSize countOptimalSize() override;
	QSize countCurrentSize(int newWidth) override;

	TextSelection toDescriptionSelection(TextSelection selection) const;
	TextSelection fromDescriptionSelection(TextSelection selection) const;

	const not_null<Data::LocationThumbnail*> _data;
	Ui::Text::String _title, _description;
	ClickHandlerPtr _link;

	int fullWidth() const;
	int fullHeight() const;

};

} // namespace HistoryView
