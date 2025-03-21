/*
 * Synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2024 Symless Ltd.
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "license_notices.h"

#include "constants.h"
#include "gui/styles.h"
#include "synergy/license/License.h"

using License = synergy::license::License;
using namespace deskflow::gui;

namespace synergy::gui {

QString trialLicenseNotice(const License &license);
QString subscriptionLicenseNotice(const License &license);

QString licenseNotice(const License &license)
{
  if (license.isTrial()) {
    return trialLicenseNotice(license);
  } else if (license.isSubscription()) {
    return subscriptionLicenseNotice(license);
  } else {
    qFatal("license notice only for time limited licenses");
    return "";
  }
}

QString trialLicenseNotice(const License &license)
{
  const QString buyLink = QString(kLinkBuy).arg(kUrlPurchase).arg(kColorWhite);
  if (license.isExpired()) {
    return QString("<p>Your trial has ended. %1</p>").arg(buyLink);
  } else {
    auto daysLeft = license.daysLeft().count();
    if (daysLeft <= 0) {
      return QString("<p>Your trial ends today. %1</p>").arg(buyLink);
    } else {
      return QString("<p>Your trial ends in %1 %2. %3</p>")
          .arg(daysLeft)
          .arg((daysLeft == 1) ? "day" : "days")
          .arg(buyLink);
    }
  }
}

QString subscriptionLicenseNotice(const License &license)
{
  const QString renewLink = QString(kLinkRenew).arg(kUrlPurchase).arg(kColorWhite);
  if (license.isExpired()) {
    return QString("<p>Your license has ended. %1</p>").arg(renewLink);
  } else {
    auto daysLeft = license.daysLeft().count();
    if (daysLeft <= 0) {
      return QString("<p>Your license ends today. %1</p>").arg(renewLink);
    } else {
      return QString("<p>Your license ends in %1 %2. %3</p>")
          .arg(daysLeft)
          .arg((daysLeft == 1) ? "day" : "days")
          .arg(renewLink);
    }
  }
}

} // namespace synergy::gui
