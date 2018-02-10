package ch.fablabs.fabjam.cocktail.boot;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.web.servlet.FilterRegistrationBean;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@Configuration
@EnableWebSecurity
public class WebConfig extends WebSecurityConfigurerAdapter {

	@Bean
	public FilterRegistrationBean httpFilter() {
		return new FilterRegistrationBean(new Filter() {
			@Override
			public void init(FilterConfig filterConfig) throws ServletException {

			}

			@Override
			public void doFilter(ServletRequest req, ServletResponse res, FilterChain filterChain) throws IOException, ServletException {
				HttpServletRequest request = (HttpServletRequest) req;
				HttpServletResponse response = (HttpServletResponse) res;
				response.setHeader("Access-Control-Allow-Origin", "*");
				response.setHeader("Access-Control-Allow-Methods", "POST, PUT, DELETE, GET, OPTIONS");
				filterChain.doFilter(req, res);
			}

			@Override
			public void destroy() {

			}
		});
	}


	@Override
	protected void configure(HttpSecurity http) throws Exception {
		http
			.csrf().disable();
		http
			.authorizeRequests().anyRequest().permitAll();
//		http
//			.authorizeRequests()
//			.antMatchers("/wl/*").permitAll()
//			.antMatchers("/dev/*").permitAll()
//			.antMatchers("/wl/system/*").hasRole("SYSTEM")
//			.and()
//			.httpBasic();
//		http
//			.headers()
//			.cacheControl().disable()
//			.frameOptions().sameOrigin();
	}

}
