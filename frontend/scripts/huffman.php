<?php
class Huffman {

    protected $root = null;

    protected $merged_frequency_map;
    
    protected $frequency_map;
    
    function __construct($array){
        $frequency_map = array();
        
        $keys = array_keys($array);

        for($i = 0; $i < sizeof($array); $i++){
            if(!array_key_exists($array[$keys[$i]], $frequency_map)){
                $frequency = 0;
                for($j = $i; $j < sizeof($array); $j++){
                    if($array[$keys[$j]] == $array[$keys[$i]]) $frequency++;
                }

                $frequency_map[$array[$keys[$i]]] = $frequency;
            }
        }

        asort($frequency_map);
        print_r($frequency_map);
        $this->buildTree($frequency_map);
    }
	
    public function buildTree($frequency_map){
        $merged_frequency_queue = array();
        $frequency_queue = array();
        foreach ($frequency_map as $value => $frequency) {
            $node = new HuffmanNode($value, $frequency);
            array_push($frequency_queue,$node);
        }
        
        while((sizeof($merged_frequency_queue) + sizeof($frequency_queue)) > 1){
            $first = $this->removeSmallest($frequency_queue, $merged_frequency_queue);
            $second = $this->removeSmallest($frequency_queue, $merged_frequency_queue);

            $combined = $first->frequency + $second->frequency;

            $merged = new HuffmanNode(null, $combined);
            $merged->left = $first;
            $merged->right = $second;
            array_push($merged_frequency_queue, $merged);            
        }

        if(empty($merged_frequency_queue)){
            $this->root = $frequency_queue[0];
        }
        else{
            $this->root = $merged_frequency_queue[0];
        }
    }
    
    public function removeSmallest(&$frequency_queue, &$merged_frequency_queue){
        $frequency_size = sizeof($frequency_queue);
        $merge_size = sizeof($merged_frequency_queue);

        if($frequency_size == 0){
            $elem = array_shift($merged_frequency_queue);
            return $elem;
        }
        
        if($merge_size == 0){
            $elem = array_shift($frequency_queue);
            return $elem;
        }

        if ($merged_frequency_queue[0] < $frequency_queue[0]){
            $elem = array_shift($merged_frequency_queue);
            return $elem;
        }        
        $elem = array_shift($frequency_queue);
        return $elem;
    }
}

class HuffmanNode {

    
    public $value;

    public $frequency;
	
    public $left = null;
    
    public $right = null;

    function __construct($value, $frequency) {
        $this->value = $value;
        $this->frequency = $frequency;
    }

    function isLeaf() {
        return ($this->left == null && $this->right == null);
    }
	
}

?>
