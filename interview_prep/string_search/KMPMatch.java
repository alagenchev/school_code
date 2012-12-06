/**
 * * Knuth-Morris-Pratt Algorithm for Pattern Matching
 * */
public class KMPMatch
{

	private String _pattern;
	private int[] _failure;

	public KMPMatch(String pattern)
	{
		_failure = new int[pattern.length()];
		_pattern = pattern;

	}

	/**
	 * * Finds the first occurrence of the pattern in the text.
	 * 
	 * @throws Exception
	 * */
	
	//the main idea is that if we have a portion of the text that matches the pattern
	//but then we have a character after that portion that matches that breaks the match, 
	//we want to shift the pattern forward in the text as much as possible so as to not 
	//just shift the pattern one character forward and recheck all characters. 
	//the longest prefix of the pattern that is also a suffix of the pattern up to the matching point
	//can be shifted in a way as to align with the portion of the pattern that was matching
	public int match(String text) throws Exception
	{
		int matchpoint = -1;
		if (_failure == null)
		{
			throw new Exception("call computeFailure first");
		}

		int j = 0;//j stores the length of the string that is 
		//part of the pattern that matches with portion in the text
		//if j becomes equal to pattern length, we've found a complete match
		
		if (text.length() == 0)
		{
			return -1;
		}

		for (int i = 0; i < text.length(); i++)
		{
			//in case we have a mismatch we want to shift the pattern to the 
			//right so as to have our prefix align to what was matched
			while (j > 0 && _pattern.charAt(j) != text.charAt(i))
			{
				//this is the same as moving the index j that is indexing
				//into the pattern to right after the longest prefix that is 
				//also a suffix of the portion of the pattern that had a complete match
				j = _failure[j - 1];
			}
			
			//if we have a match of the next character
			//increase the length of the matched pattern
			if (_pattern.charAt(j) == text.charAt(i))
			{
				j++;
			}

			//we've found a match
			if (j == _pattern.length())
			{
				//the beginning index of the match
				//is equal to the index of how far into the text we've gown 
				// minus the length of the pattern + 1
				matchpoint = i - _pattern.length() + 1;
				return matchpoint;
			}
		}
		return -1;
	}

	/**
	 * * Computes the failure function using a boot-strapping process, * where
	 * the pattern is matched against itself.
	 * */
	public int[] computeFailure()
	{

		int j = 0;

		// we are going through the whole pattern
		// from the beginning of the string to the currently checked length i
		// for each portion that we check, we will try to incrementally find the
		// largest prefix
		// that is also a suffix and store its length into a table.
		// we start at 1 since, the first suffix starts at 1
		// we don't have a suffix at 0
		//for each position find the largest prefix that is also a suffix
		for (int i = 1; i < _pattern.length(); i++)
		{
			// if the next character that we are checking in the pattern
			// isn't equal to the next character in the currently longest prefix
			while (j > 0 && _pattern.charAt(j) != _pattern.charAt(i))
			{
				// we fall back to the longest prefix of the prefix that we
				// didn't match with
				// to check if we have match with it, we continue falling back
				// until we have a match or j becomes zero - no common chars
				j = _failure[j - 1];
			}

			// if the next character in text is equal to the character in the
			// the current
			// longest substring, increase j, since we have a longer prefix
			// match
			if (_pattern.charAt(j) == _pattern.charAt(i))
			{
				j++;
			}
			// the length of the longest prefix for this portion of the pattern
			// is equal
			// to the j we computed, so store j in the table for this i
			_failure[i] = j;
		}

		return _failure;
	}
}

