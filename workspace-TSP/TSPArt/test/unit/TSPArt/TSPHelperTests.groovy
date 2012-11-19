package TSPArt

import static org.junit.Assert.*

import grails.test.mixin.*
import grails.test.mixin.support.*

import org.apache.tools.ant.taskdefs.optional.junit.JUnitTest;
import org.junit.*

/**
 * See the API for {@link grails.test.mixin.support.GrailsUnitTestMixin} for usage instructions
 */
@TestMixin(GrailsUnitTestMixin)
class TSPHelperTests extends JUnitTest{

	Tour tour;
	
	@Before
    void setUp() {
        tour = new Tour()
		tour.Lines.add(new TSPLine(0, 0, 20, 20))
		tour.Lines.add(new TSPLine(0, 0, 0, 30))
		tour.Lines.add(new TSPLine(20, 10, 20, 20))
		
		tour.Lines.add(new TSPLine(-10, 10, 20, 10))
		tour.Lines.add(new TSPLine(-10, 10, -10, 20))
		tour.Lines.add(new TSPLine(-10, 20, 0, 30))
    }

    void tearDown() {
        // Tear down logic here
    }

	@Test
    void testNonAdj() {
        TSPHelper helper = new TSPHelper()
		def line = new TSPLine(-10, 10, 20, 10)
		def nonAdjLine = helper.getNonAdjacentLine(line, tour)
		//assert nonAdjLine.
		println ""
    }
	@Test
	void testApply2Opt()
	{
		TSPHelper helper = new TSPHelper()
		helper.apply2Opt(tour)
	}
	@Test
	void testNonAdj2() {
		TSPHelper helper = new TSPHelper()
		def line = new TSPLine(-10, 20, -10, 10)
		def nonAdjLine = helper.getNonAdjacentLine(line, tour)
		//assert nonAdjLine.
		println ""
	}
	
	@Test
	void testNonAdj3() {
		tour = new Tour()
		tour.Lines.add(new TSPLine(0, 0, 20, 20))
		tour.Lines.add(new TSPLine(0, 0, -10, 10))
		tour.Lines.add(new TSPLine(20, 10, 20, 20))
		
		tour.Lines.add(new TSPLine(20, 10, 0, 30))
		tour.Lines.add(new TSPLine(-10, 10, -10, 20))
		tour.Lines.add(new TSPLine(-10, 20, 0, 30))
		
		TSPHelper helper = new TSPHelper()
		helper.apply2Opt(tour)
		//def line = new TSPLine(-10, 10, 0, 0)
		//def nonAdjLine = helper.getNonAdjacentLine(line, tour)
		//assert nonAdjLine.
		//println ""
	}
}
