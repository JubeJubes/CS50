

    select distinct(name) from people
    join stars on people.id = stars.person_id
    join movies on movies.id = stars.movie_id
    where title in (
        select title from movies
        join stars on movies.id = stars.movie_id
        join people on people.id = stars.person_id
        where name = 'Kevin Bacon' and birth = '1958'
    )
    and name != 'Kevin Bacon' order by name;

    -- select * from people where name = 'Kevin Bacon';