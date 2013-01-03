import java.util.*;

class Main
{
    public static void main(String []args)
    {
        String []temp = args[0].split(" ");
        ArrayList<Person> people = new ArrayList<Person>();

        for(String s : temp)
        {
            String [] temp2 = s.split(",");
            Person person = new Person(Integer.parseInt(temp2[0]), 
                    Integer.parseInt(temp2[1]));
            people.add(person);
        }

        for(Person person:people)
        {
            System.out.println(person);
        }

        RadixSort sort = new RadixSort();
        Person[] result = sort.SortWeight(people.toArray(new Person[people.size()]));

        result = sort.SortWeight(result);
        System.out.println("sorted:");

        for(Person person:result)
        {
            System.out.println(person);
        }
        System.out.println();
        getLongestTower(result);

    }

    private static void getLongestTower(Person []people)
    {
        ArrayList<Person> maxTower = new ArrayList<Person>();
        ArrayList<Person> currentTower = new ArrayList<Person>();

        Person lastPerson = new Person(-1,-1);

        for(Person person : people)
        {
            if(person.Height > lastPerson.Height && person.Weight > lastPerson.Weight)
            {
                currentTower.add(person);
                lastPerson = person;
            }
            else if(currentTower.size() > maxTower.size() )
            {
                lastPerson = new Person(-1, -1);
                maxTower = currentTower;
                currentTower = new ArrayList<Person>();
            }

            if(currentTower.size() > maxTower.size() 
                    && person == people[people.length - 1])
            {
                maxTower = currentTower;
            }
        }

        System.out.println("longest tower: ");
        for(Person person : maxTower)
        {
            System.out.println(person);
        }
    }


}
