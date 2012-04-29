<?php

require_once 'comparable.inc';

define ('MAX_SIZE', 1024);

class Date implements Comparable {

	public static $DATE_TIME = '%Y-%m-%d %H:%M:%S';
	public static $DB2_FORMAT = '%Y-%m-%d %H:%M:%S.000000';
	public static $PLOT_FORMAT = '%Y-%m-1 01:00:00.000000';
	public static $LONG_FORMAT = '%a, %b %d at %I:%M %p';
	public static $LONG_FORMAT_YEAR = '%a, %b %d %Y at %I:%M %p';
	public static $SHORT_FORMAT = '%D %I:%M %p';
	public static $EVENT_FORMAT = '%b %d, %Y';
	public static $EXCEL_FORMAT = '%D %I:%M %p';
	public static $DATE_FORMAT = '%m/%d/%Y';
	public static $FILE_FORMAT = '%Y_%m_%d';
	public static $UTC_FORMAT = '%d-%h-%Y %I:%M:%S %p';
	public static $CONFIGURATION_FORMAT = '%Y-%m-%d %H:%M';
	public static $SOAP_FORMAT = '%Y-%m-%dT%H:%M:%S';
	public static $SIMPLE_YEAR_MONTH_DAY = '%Y-%m-%d';
	public static $WAIVER_FORMAT = '%b %d, %Y at %H:%M';

	public static $SECOND = 1;
	public static $MINUTE = 60;
	public static $HOUR = 3600;
	public static $DAY = 86400;

	private $time;					// time value, unix time

	public function __construct ($time = false) {

		if (!$time) {													 // current time
			$this->time = time();
		} else if (is_a ($time, __CLASS__)) {	 // clone another Date
			$this->time = $time->getTime ();

		} else if (strlen ($time) > MAX_SIZE) { // size check
			throw new Exception ('Given time value data is way too large to parse.');

		} else {																// try to parse

			if (sscanf ($time, "%4d-%2d-%2d %2d:%2d:%2d", $yr, $mo, $dy, $hr, $mn, $sc) == 6) {
				$this->time = mktime ($hr, $mn, $sc, $mo, $dy, $yr);
			} else {
				$this->time = strtotime ($time);
			}

			if (!$this->time) {
				throw new Exception ('Unable to parse Date value of ' . $time . '.');
			}
		}
	}

	public function getTime () {
		return $this->time;
	}

	public function getTimestamp () {
		return $this->format (self::$DATE_TIME);
	}

	public function getWaiverFormat() {
		return $this->format (self::$WAIVER_FORMAT);
	}

	public function getDate() {
		return Date::formatDate($this->time, DATE::$DATE_FORMAT);
	}

	public function compare (Date $other) {
		return $this->time - $other->getTime ();
	}

	public function earlierThan (Date $other) {
		return ($this->compare ($other) < 0);
	}

	public function laterThan (Date $other) {
		return ($this->compare ($other) > 0);
	}

	public function sameTimeAs (Date $other) {
		return (strcmp ($this->format (self::$CONFIGURATION_FORMAT), $other->format (self::$CONFIGURATION_FORMAT)) == 0);
	}

	public function sameDayAs (Date $other) {
		return (strcmp ($this->format (self::$DATE_FORMAT), $other->format (self::$DATE_FORMAT)) == 0);
	}

	public function setLaterThan (Date $other) {

		if (!$this->sameDayAs ($other)) {
			throw new Exception ('This method may only be used on Dates that are the same day.');
		}

		$this->time = $other->getTime () + 60;
	}

	public function equals ($other) {
		return ($this->compare ($other) == 0);
	}

	public function format ($format) {
		return strftime ($format, $this->time);
	}

	public function getSimpleDate() {
		return $this->format(self::$SIMPLE_YEAR_MONTH_DAY);
	}

	public function __toString () {
		return $this->format (self::$EVENT_FORMAT);
	}

	/**
	 * Format a DB2 timestamp to a string.
	 */
	public static function formatDate ($date, $format = false) {
		list ($yr, $mo, $dy, $hr, $mn, $sc) = sscanf ($date, "%4d-%2d-%2d %2d:%2d:%2d");
		$timestamp = mktime ($hr, $mn, $sc, $mo, $dy, $yr);

		// error making time, return what was passed
		if ($timestamp < 0)
			return $date;

		// if the year is not the current year then append it
		if (!$format) {
			$format = (date ('Y') > $yr) ? self::$LONG_FORMAT_YEAR : self::$LONG_FORMAT;
		}

		return strftime ($format, $timestamp);
	}
	
    /**
	 * Get the first of the month.
	 */
	public static function firstOfMonth ($date = false, $format = false) {
	    if (!$date) {
	       $date = time();
	    }
		list ($yr, $mo, $dy, $hr, $mn, $sc) = sscanf ($date, "%4d-%2d-%2d %2d:%2d:%2d");
		$timestamp = mktime ($hr, $mn, $sc, $mo, 1, $yr);

		// error making time, return what was passed
		if ($timestamp < 0)
			return $date;

		return strftime (self::$DATE_TIME, $timestamp);
	}

	/**
	 * Current timestamp in DB2 format (for prepared statements).
	 */
	public static function currentTimestamp ($format = false) {

		if (!$format) {
			$format = self::$DB2_FORMAT;
		}

		return strftime ($format);
	}

	public static function guessDateOrNew($date) {
		$temp = self::guessDate($date);
		if ($temp == null) {
			return new Date();
		} else {
			return $temp;
		}
	}

	/**
	 * Guess a date given and return it in DB2 format.
	 */
	public static function guessDate ($date) {
		if (!$date) {
			return null;
		}

		$timestamp = strtotime (trim ($date));

		if (!$timestamp) {
			return null;
		}

		return strftime (self::$DB2_FORMAT, $timestamp);
	}

	/**
	 * Returns time between start and end time, interval defaults to second, if not specified
	 * @param $startTime
	 * @param $endTime
	 * @param $interval (SECOND, MINUTE, HOUR, DAY) Use the static variable definted in this class
	 */
	public static function getTimeDifference (Date $startTime, Date $endTime, $interval = null) {
		if (!$interval) {
			 $interval = Date::$SECOND;
		}
		return round ((($endTime->getTime () - $startTime->getTime ()) / $interval), 6);
	}
}
?>
