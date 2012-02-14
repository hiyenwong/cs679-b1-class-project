<?php
include 'tooltip.inc';

class SearchElement {

	private $name;
	private $link;
	private $tooltip;
	private $onclick;
	private $title;
	private $isButton;
	private $target;

	public function __construct ($name, $link = null, $target = null, $tooltip = null,
			$onclick = null, $title = null, $isbutton = false) {
		$this->name = $name;
		$this->link = $link;
		$this->tooltip = $tooltip;
		$this->onclick = $onclick;
		$this->title = $title;
		$this->isButton = $isbutton;
		$this->target = $target;
	}

	public function getName () {
		return $this->name;
	}

	public function getLink () {
		return $this->link;
	}

	public function getTooltip () {
		return $this->tooltip;
	}

	public function getOnclick () {
		return $this->onclick;
	}

	public function hasTooltip () {
		return ($this->tooltip);
	}

	public function hasOnclick () {
		return ($this->onclick);
	}

	public function __toString () {
		$value = "";

		if ($this->link) {
			$value = '<a href="' . $this->link . '"';

			if ($this->target) {
				$value .= ' target="' . $this->target . '"';
			}

			if ($this->onclick) {
				$value .= ' onclick="' . $this->onclick . '"';
			}

			if ($this->tooltip) {
				$value .= ' id="trigger_' . $this->tooltip->getId () . '"';
			} else {
				$value .= ' id="id_'.rand(0, 100).'"';
			}

			$value .= ($this->isButton ? ' class="button"' : '')
				. ($this->title ? ' title="'.$this->title.'"' : '')
				. '>' . $this->name . '</a>';
		} else if ($this->onclick) {
			$value = '<a style="cursor:pointer" onclick="' . $this->onclick . '"';

			if ($this->tooltip) {
				$value .= ' id="trigger_' . $this->tooltip->getId () . '"';
			}

			$value .= ($this->isButton ? ' class="button"' : '')
				. ($this->title ? ' title="'.$this->title.'"' : '') . '>'
				. $this->name . '</a>';
		} else if ($this->tooltip) {
			$value = '<span id="trigger_' . $this->tooltip->getId () . '">' . $this->name . '</span>';
		} else {
			$value = $this->name;
		}

		return $value;
	}
}
?>